#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace gyp {
  class song_map {
    public:
      int track_number;
      int bpm;
      int base_fraction;
      int difficulty;
      int song_duration; // In ms
      int object_count;
      int offset; // In ms
      std::string song_author;
      std::string name;
      std::string map_author;
      std::string difficulty_name;
      std::string music_path;
      std::vector< std::vector<int > > notes;
      song_map();
      ~song_map();
      void load(const char * filename);
      void save(const char * filename);
      void load(std::string filename);
      void save(std::string filename);
  };

  class song_map_db {
    private:
      std::vector<std::pair<std::string, song_map>> content;
    public:
      int song_map_number;
      song_map_db();
      ~song_map_db();
      void load(const char * filename);
      void save(const char * filename);
      void load(std::string filename);
      void save(std::string filename);
      void import_song_map(const char * path);
      template <typename Compare>
      void sort(Compare comp);
      song_map& operator[](size_t index);
  };
}

#endif // _MAP_HPP_
