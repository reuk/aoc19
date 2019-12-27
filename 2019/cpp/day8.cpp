#include <catch2/catch.hpp>

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

namespace {

constexpr char input[] =
    R"(222002211220222222222222210222122222222222122120222202222220222221202022222222222222022212221222222222222222022201222220222221222222222212222222222222222012210220222222222222221222122222222222022121222202222220222221212222222202222222022222221222222222222222022202222222222221222222222222222222022222222122210222222222222222022222022222222222022122222212222221222221222222222222222222022222220222222222222222222022222222222222222222222222222222122222222112221202222222222222111222022222222222122022222212222222222222212122222202222222222212220222222222222222022110222222222220222222222202222222022222222212211210222222222222022222022222222222222220222222222222222220202122222212222222222222220222222222222222222011222220222221222222222222222222222222222212201202222222222222212222022222222222022122222202222221222221212022222212222222022222220222222222222222222112222220222221222222220212202222122202222122200200222222222222110222222222222222202020222222222221222222212022222202222222222212222222222222222222222202222220222220222222222212212222022222222022201212222222222222210222222222222222012122222202222221222222222222222222222222022222220222222222222222221010222221222220222221220202212222222202222022201210222222222222010222222222222222202022222212222222222222202222222202222222022212220222222222222222120110222222222222222221220212202222222212222012202211222222222222100222022222222222222020222212222222222220222122222222221222222202221222222222222222222012222220222221222220222202212222122202222212220212222222222222020222022222222222012021222222222221222221202122222202221222122202222222222222222222021200222220222222222220221202202222222222222002202202222222222222121222122222222222002120222212222220222220202122222222221222222202220222222222222222220021222220222220222222222212222222122222222222221021222222222222222222022222222222022222222222222220222221222222222202222222222212222222222222222222221101222221222222222222221222212222222222222012220002222222222222010222122222222222112120222222222221222221212222222212222222222222222222222222222202020002222222222221222222211222212222122222222112222012222222222222110222022222222222222122222202222221222222222222222212221222102202222222222222222222221010222222222220222220202202202222222212222122220101222222222222120222022222222222202022222202222222222220222122222212222222012212201222222222222212222121222220222221222221222222212222122222122002220012222222222222201222122222222222202222222202222222222220222022222222220222222202210222222222222222222022222220222222222222211212202222122202222002220002222222222222020222022222222222102122222212222220222221202122220212221222222212200222222222222222022021222222222220222222211222202022022222222002202010222222222222212222122222222222222222222212222220222220202222222222221222122212212222222222222202222101222220222220222222210202201022022222222022210012222222222222022222222222222222212020122222222222222222212122222222220222202202222222222222222202221210222220222220222221211222202222022202222102212221222222222222122222122222222222202222122212222222222220212122220222220222122202202222222222222202121012222221222222222222221222212122222222120222222202222222222222020222022222222222102121122212222220222220202222220212220222102212222222222222222212121121222221222220222222211222220022022202121112212220222222222222211222122222222222222021222212222222222221202022222212220222102202222222222222222202220202222220222220222220202212201222222222220012212112212222222222222222122222222222112022222212222221222221202222221202222222202202211222222222222222221210222220222220222222221202200122222222221002210000202222222222122222222222222222102122022202222220222222222022222202221222212202200222222222222212120001222222222221222220211212222022122202021002202122202222222222111222222222222222002221022202222221222201212022222202220222012202210222222222222212122120222220222221222220200222221222122222121202221221212222222222201222122222222222202120222202222221222221222022221222221222022202201222222222222202021000222222222222222220210222220122022212021222201210212222222222220222022222222222022121022212222221222210222122221202222222202222211222222222222212220211222221222220222221221212221022122202020012222122202222222222020222022222222222002122022202222220222222222022221212220222002012222222222222222212021010222220222222222222200222220122222222122222202000202222222222022222222222222222122020022222222222222210212012220212222222022222221222222222222222222120222220222221222220201222202222222222222112201121212222222222202222122222222222012221022212222221222221222112220202222222222212210222222222222212022011222220222220222222220212222022222212122222201200222222222222221222222222222222112120022212222221222212212022220212221222112102201222222222222202022101222220222120222220211202212122122202220022211221212222222222010222122222222222202021122212222221022212222122222222221222102022211222222222222212121211222222222222222220210222212122122222121012222110222222222222012222122222221222122220222202222222022212202102220212222222102202211222222222222202220221222222222221222222222222211102122202122022220121202222222222011222220222220222212120222202222220022201202012221202222222022012222222222222222212120120222222222020222221222212201202022222020212212120202222222222000222122222221222212021122202222221122222212102222212021222102002212222222222222202222211222222222020222222211212222102122202221122201100212222222222110222121222222222122222222212222221022221222122221222021222002002220222222222222212121200222220222121222220222212212202122202122222222221212222222222010222020202220222222122122202222222122222202012222202021222102002221222222222222222020002222222222221222222220222201112222202220022220011222222222222121222220222221222002020022202222221122211202102220212222222002112221222222222222202222121222222222220222222200202221222022212221102201121212222222222201222221222222222212120022212222222022201202102221202202222222122211222222222222202121122222220222220222221212202202222222212222122221120222222222222001222122222220222022021022212222220022210222222221200012222112012200222222222222222020222222220222121222220200212211212122202220002221110200222222222201222120212222222202221122202222222022202222122220212211222022012212222222222222202122200222221222122122222201202201102222212120222221202212222222222200222221212220222222021122222222220022221202122221200002222022202212222222222222202202201222221222122222220212202200122222222121122222221201222220222101222020202220222022121122212222222122220212202220202200222112102200222222222222202111111222222222121122222101222201102022212120222221201201222221220110222122212222222022022022222222220122102202122220210111222212102221222222222222210212121222221222121122222100212220002222102020212200110221222220220212222220222220222112220222212222220222001222002222221212222112002210222222222222220201111222220222220022222220212221122222212020112212100212222222220112222221222020222012122122212222222122020202122222210102222112222212222222222222220022110222221222120022222200201212122022222122212202120201222222221202222120202220222002021222212222222222112222122221220222222202122212222222222222211220220222221222002022220212201200022221122020102202200212222221221201222221202122222122220122212222222122110202122221221201222112012220222222222222221121120222222222202022222222202220212022002022012222022222122220221112222020212020222112022122212222222222121222102222221120222022012210222222222222202202002222221222210022220112211201112221212022112221002102202220221202222021212120222122121022202222220122212212202222221121222202102212222222222222220022110222220222001022222221211212012120122120222110200012112221222101222122202220222112020022212222221122011212022220202001202022022221222222222222220100010222220222111122220201200220022221102221112221012012102220122100222021202222222112020022212222221222112222222222211010222210022222222222222222212211120222221222201122222201222222022221012222222010202021122220022011222020222020222022121122212222220222221212202222212002222021122212222222222222211012111222221222202122221221221221102120212221222120020002000220020221222122212022222012220222212222222022212202112220211220202101222220222222222222211110102222220222122022220100210201122220112220022001221202101221021110222120212221222012021222222222221022200212012221212111202020102222222202222222212000222222221222002122222111211002112122202020112010202000010220022102202120202121222122021122212222221222221212122222221101222220222220222212222222200201212222220222211122222212221202022020102020001120221021021222121021202222212122222012222221202222221022222222122221201010222212202222222222222222222102111222220222000022221212222122012122002120001220000202200222221001212222222222222202220022222222221022000222102220201000222111112222222202222222202211120222220222022022222020201222022020110021112021010021002220221210212222202022222122021021212222220122110202202222200122212220222211222212222222221221102222221222011122221112212011112121202222002120211112112220122001222221222020222022120222202222221022211202122221220200212122212200222222222222222022000222221222010022220212211220012022120122122102100210022220221201202121222020222212122020212222221222111222202221211110222011012221222202222222222001220222220222222122222002202012202021102020120220102220202221121112202202212122222122220122202222220222010222222222201221212100002210222202222222220200121222222222110022221022211010212220110020020120200102110221021122212110202120222212122201222222221222202222102222220010212210122220222222222222201022111022220222110022221022202221222121220220010212100222102220021122222200222122222012021021222222221222020212212221211111222000222212222212222222200210001222221222212122221100220020012121221022001221012011010220120220222121222221222112022012202222221122121202002220202120202010112211222222222022211210220022222222012022220222200200102022021222010121012022112222122020212220202222222222120020212222221222101212022221222111222200212220222202222122210202022122221222002022221100200112022121001122022221001021011221120111202100212121222222022201202222121122201202012221200021212022122200222212222122210111220122222222202222222122211202222120202022101210011200221222022111212202202222022112022111202222121122212222212222201210222210212202222222222122210111122122222222222022220000200122012222010121001122210201122222121200212012202220222112121110222222222122001212022221200012202211202222222212222022222200010122221222221122220202222212222120110220111102122122200222020201202000222021022212021200222222121022010212022221220012222110212200222202222220222211221222221222000222221120212011112222002221112121221110210222022221212101212020022002222010202222220222012202102220211012212112222200222202222221212011210222221222120122220212220211212121010100210001122120102222020101202112222120022212022002202222221122220202012222202010212010012210022222222222202022122022222222010022220221202221022122100122101110120120202220221102200211222121122102022210212221120122121222002222211110212102002210221212222121200222100222222222222122220222212202102121000221021020120111000220221100210200212222122212120022202221221222111222112222202102222102012212222202222121221101102122221222010222221011220121002122202211011102220020010222122112210112202122222202022221222222020222001202112220200220220212212211020212222221201021201222220222122122220111212101022021222022200101002201101222022111220202222122022012220211202222221022202222012221222021200000112222021222222121211222021222221222202122222122220201212121201011022000121020101221222222200122212220122112020101212221122122011212012222201122211221022221220222222121200111020022221222011122220202222211022121212000012020100200220222120220201011202220022222220020222221222222112222012220222222200221022221220222222220211000000222222222102022222010202001112021220200201211001210012222120010202120222122122022020122202222021122102212002222222122211220202212122212222020202010020122220222010022222102201121111021111211102222112222112221220012211011202121222220120001222220122022001222122220210210222110122212020222222020201202122112221222202122220200210212100220101011202120102020102222121101211112212022222222021201202220121122020202112222201220210211022200122222222021200102022102202222121122221111201222110020111210001221011101111221221120221202202121222000221121202222121222001202002222212010212110102220220220222120220010211222221222121222221021210111100022010212121220010102101220020121211022202120022212220002212221222222000202112220202110202012102202021220222220212100001112201222000222222201212121001021200202111022122002012220220011212011202222222122222100202220222222102212102220210120210102102201021221022201221000222112221222211122220220210211221120020202212100102010220221221120220022212121022010021210202220121122121202022222122102212110022202021200222202200121110112212222001022220001201101112122021011010200011110011221221122202000212121022010221002202220020222210222212222002000201000122222121222022120212102021102220220212122220011211012102220102010020011221121201220222012220121222221222212020000202222021020221212012220010021210021202201220202112001210210100212211221201022221220222000111221010122200211201022012220220010211111222120222011021221222220121220212212002221011121210221022220220211202211221112221202222221100122220111222100112220121200222220102222112221021221210121212000222021122110202221221022012202102221012121211202202202222220122222220110012212201220210122220120222211022022212101010222011220000222020102222012012010122020122201212220221120020222222222001211200202202211022222012110200222010202201220222022221012000110101022201110201222112010121222122111222002122110022022220001212220120022101202222222100210221121012202122222022002211011012202200220110022222201212000112121121221012021202200220220021110221100112222122122000102222221022022022222112222102012222121002202220222202010222211121002221221020122220100020202022220100000120102110212122220021102201001012122122011222120212220201221010212202221212012222022222221121202202012202220221022220221110222222000202100020102122100122011012022010220022002211112112022022202111022212211022221112222002220010102200102222121221200202202200221110122110220000022221201121101111012100000200120211112211221120110201221002201022200100210212220002222020212102222110012222122012220221221100100200020201202111221010122222121221100012201222102001021121201111221020200211020222111222011120101202222201220200202102222110212210111222021021220211020220110001112021222121222222221220202100210102111010022110202200220122210202000102212022220001200202211211021210222222222100022222001022210120212001111202010201222202221122122220020120100101120222211201000201210102222221021201220212000022110112002202212121220102202122220101211220100222101020202000012102201220202002221011221220201021101100221021202222121102210012101211100012102100202110121020200000022202002101110020002120110021210010212102012021222211212200010211100121212012001010222122112011)";

enum class Colour { transparent, black, white };

} // namespace

TEST_CASE("day8") {
  constexpr auto width = 25;
  constexpr auto height = 6;
  constexpr auto pixelsPerLayer = width * height;

  using std::begin, std::end, std::size;
  constexpr auto pixels = size(input);

  std::vector<decltype(begin(input))> layers;

  for (auto i = 0; i + pixelsPerLayer < pixels; i += pixelsPerLayer)
    layers.push_back(input + i);

  const auto countInLayer = [&](const char *start, char elem) {
    return std::count(start, start + pixelsPerLayer, elem);
  };

  const auto layerWithFewestZeros = std::min_element(
      begin(layers), end(layers), [&](const char *a, const char *b) {
        return countInLayer(a, '0') < countInLayer(b, '0');
      });

  if (layerWithFewestZeros == end(layers))
    throw std::runtime_error{"fail"};

  const auto checksum = countInLayer(*layerWithFewestZeros, '1') *
                        countInLayer(*layerWithFewestZeros, '2');

  REQUIRE(checksum == 1340);

  std::array<Colour, pixelsPerLayer> finalImage{{}};

  for (const auto it : layers) {
    for (auto i = 0; i != pixelsPerLayer; ++i) {
      auto &result = finalImage[i];

      if (result != Colour::transparent)
        continue;

      result = [&] {
        switch (it[i]) {
        case '0':
          return Colour::white;
        case '1':
          return Colour::black;
        case '2':
          return Colour::transparent;
        }

        return Colour{};
      }();
    }
  }

  if (std::any_of(begin(finalImage), end(finalImage),
                  [](auto c) { return c == Colour::transparent; }))
    throw std::runtime_error{"fail"};

  auto it = begin(finalImage);

  for (auto y = 0; y != height; ++y) {
    for (auto x = 0; x != width; ++x) {
      std::cout << (finalImage[y * width + x] == Colour::black ? 'x' : ' ');
    }
    std::cout << '\n';
  }
}