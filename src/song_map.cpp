#include "song_map.hpp"

namespace pt = boost::property_tree;

namespace gyp {
// class song_map

void song_map::load(const std::string& filename) {
  pt::ptree tree;
  pt::read_json(filename, tree);
  track_number = tree.get<int>("track_number");
  bpm = tree.get<int>("bpm");
  base_fraction = tree.get<int>("base_fraction");
  difficulty = tree.get<int>("difficulty");
  song_duration = tree.get<int>("song_duration");
  object_count = tree.get<int>("object_count");
  offset = tree.get<float>("offset");

  song_author = tree.get<std::string>("song_author");
  name = tree.get<std::string>("name");
  map_author = tree.get<std::string>("map_author");
  difficulty_name = tree.get<std::string>("difficulty_name");
  music_path = tree.get<std::string>("music_path");

  notes = std::vector<std::vector<int>>(track_number, std::vector<int>());
  for (pt::ptree::value_type &single_track : tree.get_child("notes")) {
    for (pt::ptree::value_type &single_note :
         single_track.second.get_child("time")) {
      notes[single_track.second.get<int>("track")].push_back(
          single_note.second.get_value<int>());
    }
  }
}

void song_map::save(const std::string& filename) {
  pt::ptree tree;
  tree.put("track_number", track_number);
  tree.put("bpm", bpm);
  tree.put("base_fraction", base_fraction);
  tree.put("difficulty", difficulty);
  tree.put("song_duration", song_duration);
  tree.put("object_count", object_count);
  tree.put("offset", offset);

  tree.put("song_author", song_author);
  tree.put("name", name);
  tree.put("map_author", map_author);
  tree.put("difficulty_name", difficulty_name);
  tree.put("music_path", music_path);
  pt::ptree notes_tree;
  for (int i = 0; i < track_number; i++) {
    pt::ptree single_track;
    pt::ptree single_track_time;
    for (int t : notes[i]) {
      pt::ptree single_note;
      single_note.put_value(t);
      single_track_time.push_back(std::make_pair("", single_note));
    }
    single_track.put("track", i);
    single_track.push_back(std::make_pair("time", single_track_time));
    notes_tree.push_back(std::make_pair("", single_track));
  }
  tree.push_back(std::make_pair("notes", notes_tree));
  pt::write_json(filename, tree);
}

// class song_map_db

void song_map_db::load(const std::string& filename) {
  pt::ptree tree;
  pt::read_json(filename, tree);
  tree.get<int>("song_map_number");
  for (pt::ptree::value_type &single_song : tree.get_child("song_maps")) {
    content.emplace_back(single_song.second.get_value<std::string>(),
                         song_map());
    content.back().second.load(content.back().first);
  }
}

void song_map_db::save(const std::string& filename) {
  pt::ptree tree;
  tree.put("song_map_number", song_map_number);
  pt::ptree song_maps_tree;
  for (const std::pair<std::string, song_map> &single_song : content) {
    pt::ptree single_song_path;
    single_song_path.put_value(single_song.first);
    song_maps_tree.push_back(std::make_pair("", single_song_path));
  }
  tree.push_back(std::make_pair("song_maps", song_maps_tree));
  pt::write_json(filename, tree);
}

template <typename Compare> void song_map_db::sort(Compare comp) {
  std::sort(content.begin(), content.end(), comp);
}

song_map &song_map_db::operator[](size_t index) {
  return content[index].second;
}

} // namespace gyp
