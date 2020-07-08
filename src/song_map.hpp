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
      double bpm;
      int base_fraction;
      std::string song_author;
      std::string name;
      std::string map_author;
      std::string difficulty_name;
      int difficulty;
      int song_duration; // In ms
      int object_count;
      int offset; // In ms
      song_map();
      song_map(const char * path);
      ~song_map();
      void write_json(const char * path);
      void read_json(const char * path);
  };

  class song_map_db {
    private:
      std::vector<song_map> content;
    public:
      int song_map_number;
      song_map_db();
      ~song_map_db();
      void write_json(const char * path);
      void read_json(const char * path);
      void import_song_map(const char * path);
      template <typename Compare>
      void sort(Compare comp);
      song_map& operator[](size_t index);
  };
}

#endif // _MAP_HPP_
