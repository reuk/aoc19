#include "coord.hpp"
#include "direction2d.hpp"

#include <catch2/catch.hpp>

#include <array>
#include <iostream>
#include <map>
#include <optional>
#include <queue>
#include <set>
#include <string>

namespace {

constexpr char input[] = "                               Y       P           J       L     Y N     Q   H                                     \n"
    "                               I       O           J       H     Y S     G   M                                     \n"
    "  #############################.#######.###########.#######.#####.#.#####.###.###################################  \n"
    "  #.....................#.........#...#.....#.......#.......#.#.......#.....#.........#.#.........#.#.#...#.#...#  \n"
    "  #.#.#.###.###.###.###.#.#.###.###.#.###.###.#######.#.###.#.###.###.#.###.#####.#.###.#.#########.#.###.#.#.###  \n"
    "  #.#.#.#.#.#.#.#...#...#.#.#.#.....#.#.....#.......#.#.#.#...#.....#.#.#.#.#.#...#.............#.#.#...........#  \n"
    "  #####.#.#.#.###.#.###.#####.#.#####.###.#.#####.#.#.###.#########.#####.#.#.###.###############.#.#.#.###.###.#  \n"
    "  #...#...#.#.#...#.#.#.......#.#.....#...#...#...#.#.....#.......#...#.........#...........#...#.....#.#...#.#.#  \n"
    "  ###.#.#####.#######.#.#.###.###.#.#######.###.#####.#########.###.#####.#.#######.#.#########.#.#.#######.#.###  \n"
    "  #.....#.#.#.....#.....#...#.....#.#.#.....#.....#.......#.....#...#...#.#.#.#.#...#.#.#...#...#.#...#...#.....#  \n"
    "  ###.#.#.#.#####.###.###.#####.#####.###.###.#.#.###.#.#.#.#.#.#.###.#.#.###.#.###.#.#.###.#.#.#.#######.#.#####  \n"
    "  #...#.#...#...#.#...#...#.......#.....#.#.#.#.#...#.#.#.#.#.#.....#.#.........#...#.#.....#.#.....#...#.#.#...#  \n"
    "  #.#######.#.###.###.###.#######.#.#.#.#.#.#.###.###.###.#.#.#.#####.#############.###.#######.#######.#.#####.#  \n"
    "  #.#...#...........#.#...#.........#.#.#...#.#.#.#.....#.#.#.#...#.........#...#.#.......#...........#...#.....#  \n"
    "  #.#.#####.#.###.#############.#.###.#####.#.#.#######.#####.#####.#.###.#.#.###.#.###.###.#############.#####.#  \n"
    "  #.#...#.#.#.#.......#...#.....#.#.....#.#.#.......#.#...#...#...#.#...#.#.#...#.#...#...........#.#.#.......#.#  \n"
    "  ###.#.#.#######.###.###.###########.#.#.#.###.#####.#.###.#.#.#####.#.###.#.###.#.#####.#.#.###.#.#.###.#####.#  \n"
    "  #.#.#.#.....#.#.#.#.#...............#.#...#...#...#.....#.#.....#.#.#.#.......#.....#...#.#...#.....#.#.......#  \n"
    "  #.###.#.#####.###.#.#.#######.#####.#.###.#.#####.#.#######.#####.#.###.#.#####.#######.#.###.#.#.###.#.#.#.#.#  \n"
    "  #...#...#.#.#...#...#.#.#.#.#...#.#.#.#.#.#.....#.......#.....#.#...#...#...#.........#.#...#.#.#.#.....#.#.#.#  \n"
    "  #.#####.#.#.###.###.###.#.#.#####.#.###.#.###.#######.###.#.###.#########.#####.#######################.#.###.#  \n"
    "  #.#.........#.#.#.....#...........#...#...#.#...#.#.#...#.#.#...#.........#.....#.#.#.#...#.....#...#...#.#.#.#  \n"
    "  #.#######.###.#.###.#.###########.#.###.###.#.#.#.#.###.###.#.#.#########.#####.#.#.#.###.###.###.#####.###.###  \n"
    "  #.#...#...#.....#...#...#.#.#.......#.....#...#.#.......#...#.#.#.......#...#.....................#.#...#.#.#.#  \n"
    "  #.###.###.#.#########.###.#.###.#.#.#####.#.#######.###.###.#.#######.###.#######.#.###.###.#.###.#.###.#.#.#.#  \n"
    "  #.#...#...#.#.#...#.....#.#...#.#.#.#.....#.....#.....#.#.......#.#...#.....#.#...#...#.#.#.#.#...#...#.......#  \n"
    "  #.###.#.###.#.#.###.###.#.###.###.###.###.#.###.#####.#.#.###.#.#.###.#.#.###.#.#########.#########.#.###.#####  \n"
    "  #.....#.#.#.....#.#.#...............#...#.#.#...#.....#.#.#...#...#.....#...#.......#.#.#.#.......#.#...#...#.#  \n"
    "  #####.#.#.#.#####.#####.#########.#####.###.#######.#######.#.#########.#####.#######.#.#.###.#######.#.#.#.#.#  \n"
    "  #...#...#.#.......#...#.#.#      E     Y   V       U       W L         Y     J      #...#.#...#...#.#.#.#.#.#.#  \n"
    "  ###.#.###.#.###.#.###.###.#      R     I   B       H       T D         Y     R      ###.#.#.###.###.#.###.###.#  \n"
    "  #.......#.....#.#.#...#.#.#                                                         #.............#.....#...#.#  \n"
    "  ###.###.###.#########.#.#.#                                                         #####.###.#.###.#####.###.#  \n"
    "  #.#.#.#.#.#.#.#.....#.....#                                                         #...#.#...#.#...#...#...#.#  \n"
    "  #.#.#.###.#.#.#####.#####.#                                                         #.###.#.#######.#.###.###.#  \n"
    "  #.#...#...#.#...#...#.....#                                                       JJ..#...#...#.#.....#...#.#..KB\n"
    "  #.###.###.#.###.#.#.#.#.#.#                                                         #.#.#####.#.###.###.###.#.#  \n"
    "  #...#.#.#.........#...#.#..FR                                                       #.....#...................#  \n"
    "  #.###.#.#######.#####.#.#.#                                                         ###########################  \n"
    "RX........#.....#.....#.#.#.#                                                       PO..#.....#...............#..YB\n"
    "  ###.###.###.#####.#########                                                         #.#.###.###.#.#.#.#####.#.#  \n"
    "  #.....#.............#.....#                                                         #.....#...#.#.#.#.#.......#  \n"
    "  ###.###.###.#.#.#######.###                                                         #.#######.#.#.#.#########.#  \n"
    "PU..#.#.....#.#.#...#...#.#.#                                                         #...#.....#.#.#.....#...#.#  \n"
    "  #.#.###.#######.#####.#.#.#                                                         #####.#####.###.###.###.#.#  \n"
    "  #.#.#.#...#.#...#...#......KB                                                       #.#.#.........#...#...#...#  \n"
    "  #.###.#####.#####.#####.###                                                         #.#.#####.#################  \n"
    "  #.#.#.......#...#.#.#.#...#                                                       YB......#.....#...#.......#.#  \n"
    "  #.#.#.#.#.###.###.#.#.###.#                                                         #.#.#.#########.#.#.#.###.#  \n"
    "  #.....#.#.................#                                                         #.#.#.#.......#.#.#.#.....#  \n"
    "  ###################.#######                                                         ###.#####.#####.#########.#  \n"
    "  #.#.......#.......#...#.#.#                                                         #.#...#.....#.#...#.......#  \n"
    "  #.#.#####.#.###.#.#####.#.#                                                         #.###.###.#.#.#.#######.#.#  \n"
    "  #.....#...#.#.#.#.#.#......BI                                                       #.#.#.....#.............#..LD\n"
    "  #.#######.#.#.###.#.#####.#                                                         #.#.#####.#################  \n"
    "  #.....#.......#.....#...#.#                                                         #.......#.#...#...#...#...#  \n"
    "  #.###############.###.#.#.#                                                         #.###.#.###.#.#.###.#.#.#.#  \n"
    "YT......#.......#.......#...#                                                         #.#...#...#.#.......#...#..BB\n"
    "  #####.#.###.###############                                                         #.#####.###.#.###.###.#####  \n"
    "  #...#.#.#.................#                                                       JN....#...#.#.#.#.#...#.#...#  \n"
    "  #.#.#####.#######.#.#.###.#                                                         #######.#.#.#.#.#########.#  \n"
    "  #.#.#.....#.#...#.#.#...#.#                                                         #.#.#.......#.#...#.......#  \n"
    "  #.#.#.###.#.#####.#.#####.#                                                         #.#.###########.#.#######.#  \n"
    "  #.#.#.#.#.....#.#.#.#.#...#                                                         #.....#.....#...#.#.#.....#  \n"
    "  #.#.###.#####.#.#####.###.#                                                         #.#.###.#.#.###.#.#.#.#.#.#  \n"
    "WT..#...........#.#...#.#.#..SG                                                     PU..#.#...#.#.....#.#...#.#..JN\n"
    "  ###############.#.###.#.###                                                         #.#####.###.#.#.#######.#.#  \n"
    "  #...#.#.............#.....#                                                         #.......#...#.#.....#...#.#  \n"
    "  #.#.#.#.#.#######.#.###.#.#                                                         #.###############.###.#.#.#  \n"
    "  #.#...#.#...#.....#.#...#.#                                                         #...#...#.#.#...#.....#.#.#  \n"
    "  #.#.###.#######.#####.###.#                                                         #####.###.#.###.###########  \n"
    "VB..#...#...#.........#.#.#..LH                                                       #...#.....................#  \n"
    "  #####.#.#####.###.#.#.#.#.#                                                         #.#.#####.###.#.###.#####.#  \n"
    "  #.#.#.......#.#...#.....#.#                                                       NS..#.#.#.#.#.#.#.#.#.#...#.#  \n"
    "  #.#.#####.#.#.#.#.#########                                                         ###.#.#.#.#.#.#.#.#.#.#####  \n"
    "  #...#.#.#.#.#.#.#...#...#.#                                                         #.......#...#.#.#.#...#....KU\n"
    "  #.#.#.#.###.#########.###.#                                                         #.#####.#.###.###.###.#.###  \n"
    "AA..#.......#.#.#.....#...#..DU                                                       #.#...#...#...#.#...#.....#  \n"
    "  #.###.#######.#####.#.#.#.#                                                         ###.###########.#.#########  \n"
    "  #.#...#.....#.#...#...#.#.#                                                         #.......................#.#  \n"
    "  #.#.###.#.###.###.#.###.#.#                                                         #.#.#.#.#.#.#.#.#.#####.#.#  \n"
    "ER..#.....#...........#.#...#                                                       QG..#.#.#.#.#.#.#.#.#.......#  \n"
    "  ###.#.#.###.###.#.#.#.#.#.#                                                         #.###.#.#######.#####.###.#  \n"
    "  #...#.#.#...#...#.#...#.#.#                                                         #.#...#.#.#.......#...#...#  \n"
    "  #.#.###.#.#####.#########.#                                                         #.#.#.#.#.#.###.###.#####.#  \n"
    "  #.#...#.#...#.......#.....#                                                         #.#.#.#.#...#.....#.#.#....DU\n"
    "  ###.#.###.#.###.#.#####.#.#        T         Y       H   R       K         B        ###.#####.#####.###.#.###.#  \n"
    "  #.#.#...#.#.#.#.#.#.....#.#        S         T       M   X       U         B        #...#.#.#.#.......#.#.....#  \n"
    "  #.#.#.#####.#.#.#####.#############.#########.#######.###.#######.#########.###########.#.#.#####.#.#.#.###.###  \n"
    "  #...#...#.....#...#.#.#.....#.#.......#.#.#.#.....#.....#.#.....#.#...#.......#...#...#...#.......#.#.#.#.....#  \n"
    "  ###.#######.#####.#.#######.#.###.#####.#.#.###.###.#.###.#.#.###.#.#.#####.#####.#.###.###.#.###.#########.#.#  \n"
    "  #.........#.#.......#.#.............#.....#.....#...#.#.....#.#.....#...#.....#.....#.#.#.#.#.#.#.......#...#.#  \n"
    "  #.###.#####.#######.#.###.###.#.#.#.#.#.#####.###.#####.###.#.#######.#.#.###.#.###.#.###.#.###.#.###.###.#.###  \n"
    "  #...#...#.......#.......#.#.#.#.#.#...#.#.#.....#.....#.#...#...#...#.#.#...#.....#.......#.#.....#.....#.#...#  \n"
    "  #.###.#####.#.###.###.#####.#.#.#.#.#.#.#.###.#####.###########.#.#.###.#######.###.#.#####.#.###.###.###.#####  \n"
    "  #.#...#.....#.#.#.#...#.#.#...#.#.#.#.#...#...#...........#.....#.#.......#...#...#.#.#.....#.#.....#.#.......#  \n"
    "  #.#####.#####.#.#######.#.#.#.#.#######.###.#.#.#####.###.#####.#.#####.#.###.#.###.#####.#.###.#.#######.#.#.#  \n"
    "  #.#.....#.......#.#.........#.#.#...#.....#.#.#...#.....#.#.....#.#.#...#.#.....#.#.#...#.#.#...#.#.#.....#.#.#  \n"
    "  #######.#.#.#.#.#.#########.#######.###.###.###.#####.#.###.###.#.#.#.#.###.###.#.###.###.#######.#.###.#.#.###  \n"
    "  #.......#.#.#.#.#...#.#.#...#.#.........#.....#...#...#...#.#...#...#.#...#...#.....#...#.#.#.#.....#...#.#...#  \n"
    "  #####.###.#.###.#.###.#.#####.#####.###.#.#.###.#######.#.#.###.#.###.#.#######.#####.#####.#.###########.#####  \n"
    "  #.......#.#.#...#.......#.#.......#.#.#.#.#...#.#...#...#.#.#...#...#.#.#.#.......................#.#.#.......#  \n"
    "  ###.#.#########.#######.#.#####.#.###.#.#.#.#####.#####.#######.#.#######.#####.###.#####.###.#.#.#.#.###.#.#.#  \n"
    "  #...#.#.........#.#...#.#.......#.#.....#.#.#.....#...#.#.#.....#...#.#.#.#...#.#.#.#.#...#...#.#.....#...#.#.#  \n"
    "  ###.###.###.#####.###.#.#########.#####.#.###.###.###.#.#.###.###.###.#.#.#.###.#.###.#######.#############.###  \n"
    "  #.....#.#.....#.#.................#.#...#.....#...#.#.....#.....#.#...#.#...#...............#.....#.#.........#  \n"
    "  #.###.#.#######.#.#.###.#####.###.#.###.###.#######.###.#.#####.#.#.###.#.#.#.#.###.###.#####.#.#.#.#######.###  \n"
    "  #.#...#.#...#.....#.#...#.#...#.#.........#.....#...#...#.#.#...#.......#.#.#.#.#.#...#.#.#.#.#.#.........#...#  \n"
    "  #.#####.#.###.#.###.#.###.#####.###.#####.#.###.###.###.###.#.#########.#.#.#.#.#.#.#####.#.###.#.#.###.#####.#  \n"
    "  #.#.#...#...#.#.#...#.#.#.#...#...#.....#.#...#...#...#.#.#...#.#.....#.#.#...#...#.#.#.#...#...#.#.#.......#.#  \n"
    "  #.#.#.#.#.#.###########.#.###.###.###.#####.#######.#.#.#.#.###.#.###.#.#.###########.#.#.###.#.#.#.###.#.#.###  \n"
    "  #.#...#.#.#.#.#.....#.........#.#.#...#.....#.#.....#...#.....#.#.#.#...#.#...#.#.#...#.....#.#.#.#...#.#.#...#  \n"
    "  #.###.###.#.#.###.###.###.###.#.#.###.###.###.###.#######.#####.#.#.#.#.#.#.#.#.#.###.#.#.#.#####.#.#.#.#.###.#  \n"
    "  #.#...#...#...........#.....#.........#.........#.......#.....#...#.#.#.#...#...........#.#...#...#.#.#.#.#...#  \n"
    "  ###################################.#####.#####.#######.#####.###.#############.###############################  \n"
    "                                     J     Z     F       S     T   U             B                                 \n"
    "                                     R     Z     R       G     S   H             I                                 \n";

class Map final {
  constexpr auto toInd(reuk::Coord c) const noexcept -> std::optional<size_t> {
    const auto result = c.x + width_ * c.y;

    if (c.x < 0 || width_ <= c.x || c.y < 0 || storage.size() <= result)
      return {};

    return result;
  }

  constexpr auto toCoord(int64_t ind) const noexcept {
    return reuk::Coord{ind % width_, ind / width_};
  }

public:
  constexpr explicit Map(std::string_view m)
      : storage(m), width_(storage.find('\n') + 1) {}

  constexpr auto get(reuk::Coord c) const noexcept -> std::optional<char> {
    if (const auto ind = toInd(c))
      return storage[*ind];
    return {};
  }

  constexpr auto width() const { return width_; }
  constexpr auto height() const { return storage.size() / width_; }

private:
  std::string_view storage;
  int64_t width_{};
};

struct Portal final {
  char first{}, second{};
};

constexpr auto tie(const Portal &p) { return std::tie(p.first, p.second); }
constexpr auto operator<(const Portal &a, const Portal &b) {
  return tie(a) < tie(b);
}
constexpr auto operator==(const Portal &a, const Portal &b) {
  return tie(a) == tie(b);
}

auto operator<<(std::ostream &os, const Portal &p) -> auto & {
  return os << p.first << p.second;
}

constexpr auto parsePortalTile(const Map &map, reuk::Coord c)
    -> std::optional<char> {
  if (const auto tile = map.get(c))
    if ('A' <= *tile && *tile <= 'Z')
      return *tile;

  return {};
}

constexpr auto parsePortalTiles(const Map &map, reuk::Coord a, reuk::Coord b)
    -> std::optional<Portal> {
  if (const auto u = parsePortalTile(map, a))
    if (const auto v = parsePortalTile(map, b))
      return Portal{*u, *v};

  return {};
}

constexpr auto parsePortal(const Map &map, reuk::Coord c)
    -> std::optional<Portal> {
  const auto loc = map.get(c);

  if (loc != '.')
    return {};

  for (const auto &[a, b] :
       std::array{std::tuple{reuk::Coord{-2, 0}, reuk::Coord{-1, 0}},
                  std::tuple{reuk::Coord{1, 0}, reuk::Coord{2, 0}},
                  std::tuple{reuk::Coord{0, -2}, reuk::Coord{0, -1}},
                  std::tuple{reuk::Coord{0, 1}, reuk::Coord{0, 2}}})
    if (const auto p = parsePortalTiles(map, c + a, c + b))
      return *p;

  return {};
}

auto parsePortals(const Map &map) {
  std::map<Portal, std::vector<reuk::Coord>> result;

  const auto width = map.width();
  const auto height = map.height();

  for (auto x = 0; x != width; ++x) {
    for (auto y = 0; y != height; ++y) {
      const auto c = reuk::Coord{x, y};
      if (const auto p = parsePortal(map, c))
        result[*p].push_back(c);
    }
  }

  return result;
}

auto getAdjacentTiles(
    const std::map<Portal, std::vector<reuk::Coord>> &portals) {
  std::map<reuk::Coord, reuk::Coord> adjacentTiles;

  for (const auto &[_, coords] : portals) {
    if (coords.size() == 2) {
      adjacentTiles[coords[0]] = coords[1];
      adjacentTiles[coords[1]] = coords[0];
    }
  }

  return adjacentTiles;
}

auto getNamedPortals(
    const std::map<Portal, std::vector<reuk::Coord>> &portals) {
  std::map<reuk::Coord, Portal> result;

  for (const auto &[name, coords] : portals) {
    for (const auto c : coords) {
      result.emplace(c, name);
    }
  }

  return result;
}

enum class PortalKind { outer, inner };

constexpr auto toLevelIncrement(PortalKind k) {
  switch (k) {
  case PortalKind::outer:
    return -1;
  case PortalKind::inner:
    return 1;
  }

  return 0;
}

constexpr auto getPortalKind(const Map &m, reuk::Coord c) {
  if (c.x == 2 || c.x == m.width() - 4 || c.y == 2 || c.y == m.height() - 3)
    return PortalKind::outer;
  return PortalKind::inner;
}

auto bfs(const Map &map, reuk::Coord pos, reuk::Coord target,
         const std::map<reuk::Coord, reuk::Coord> &portals) {
  struct StepInfo final {
    reuk::Coord pos;
    size_t steps{};
  };

  std::queue<StepInfo> toTry;
  toTry.push(StepInfo{pos, 0});
  std::set<reuk::Coord> discovered{pos};

  while (!toTry.empty()) {
    const auto next = toTry.front();
    toTry.pop();

    if (next.pos == target)
      return next.steps;

    const auto tryNext = [&](auto c) {
      if (discovered.find(c) != discovered.cend())
        return;

      if (map.get(c) != '.')
        return;

      discovered.insert(c);
      toTry.push(StepInfo{c, next.steps + 1});
    };

    for (const auto dir : reuk::directions2d)
      tryNext(next.pos + reuk::toCoord(dir));

    if (const auto it = portals.find(next.pos); it != portals.cend())
      tryNext(it->second);
  }

  return size_t{};
}

struct RecursiveCoord final {
  reuk::Coord pos;
  size_t level{};
};

auto operator<<(std::ostream &os, const RecursiveCoord &c) -> auto & {
  return os << c.pos << ' ' << c.level;
}

auto tie(const RecursiveCoord &c) { return std::tie(c.pos, c.level); }
auto operator<(const RecursiveCoord &a, const RecursiveCoord &b) {
  return tie(a) < tie(b);
}
auto operator==(const RecursiveCoord &a, const RecursiveCoord &b) {
  return tie(a) == tie(b);
}
auto operator!=(const RecursiveCoord &a, const RecursiveCoord &b) {
  return tie(a) != tie(b);
}

auto recursiveBfs(const Map &map, const RecursiveCoord pos,
                  const RecursiveCoord target,
                  const std::map<reuk::Coord, reuk::Coord> &portals)
    -> std::vector<RecursiveCoord> {
  std::queue<RecursiveCoord> toTry;
  toTry.push(pos);
  std::set<RecursiveCoord> discovered{pos};
  std::map<RecursiveCoord, RecursiveCoord> route;

  while (!toTry.empty()) {
    const auto next = toTry.front();
    toTry.pop();

    if (next == target) {
      std::vector<RecursiveCoord> result;

      for (auto p = target; p != pos; p = route[p])
        result.push_back(p);

      return result;
    }

    const auto tryNext = [&](RecursiveCoord c) {
      if (discovered.find(c) != discovered.cend())
        return;

      if (map.get(c.pos) != '.')
        return;

      route[c] = next;
      discovered.insert(c);
      toTry.push(c);
    };

    for (const auto dir : reuk::directions2d)
      tryNext(RecursiveCoord{next.pos + reuk::toCoord(dir), next.level});

    if (const auto it = portals.find(next.pos); it != portals.cend()) {
      const auto inc = toLevelIncrement(getPortalKind(map, next.pos));
      if (next.level != 0 || inc >= 0)
        tryNext(RecursiveCoord{it->second, next.level + inc});
    }
  }

  return {};
}

} // namespace

TEST_CASE("day20") {
  constexpr auto map = Map{input};

  const auto portals = parsePortals(map);
  const auto adjacent = getAdjacentTiles(portals);

  REQUIRE(bfs(map, portals.at(Portal{'A', 'A'}).front(),
              portals.at(Portal{'Z', 'Z'}).front(), adjacent) == 484);

  REQUIRE(recursiveBfs(map, {portals.at(Portal{'A', 'A'}).front()},
                       {portals.at(Portal{'Z', 'Z'}).front()}, adjacent)
              .size() == 5754);
}