#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>
#include <map>
#include <utility>

namespace View{

    class Edge{

        //friend int edgeID(Edge& e, std::map <std::pair<int,int>, Edge>& list) ;
        //friend bool contain(Edge& e, std::vector<Edge>& list) ;

        int _v1;
        int _v2;
        int _id;
        std::vector<int> _trig_list{};

    public:
        Edge (int i, int j):_v1(i),_v2(j)
        {
        };

        [[nodiscard]] constexpr bool operator== (const Edge & e) noexcept
        {
            return (_v1 == e._v1 && _v2 == e._v2) || (_v1 == e._v2 && _v2 == e._v1);
        }

        void add_triangle(const int trig)
        {
            for (size_t i = 0; i < _trig_list.size(); i++) 
                if (trig == _trig_list[i]) return;

            _trig_list.emplace_back(trig);
        }

        void other_trig(const int trig, std::vector<int>& others) 
        {
            for (size_t i = 0; i < _trig_list.size(); i++) {
                if (_trig_list[i] == trig) continue; 
                else others.emplace_back(_trig_list[i]);
            }
        }

        [[nodiscard]] bool contain(const Edge& e, const std::map<std::pair<int,int>,Edge>& list)
        {
            for(const auto& item: list)
            {
                if( (item.second._v1 == e._v1 && item.second._v2 == e._v2 ) ||
                    ( item.second._v2 == e._v1 && item.second._v1 == e._v2 ) )
                {
                    return true;
                }
            }

            return false;
        }

        void setId(const int id) { _id = id;};

        [[nodiscard]] constexpr int id() const { return _id;};
        [[nodiscard]] constexpr int v1() const { return _v1;};
        [[nodiscard]] constexpr int v2() const { return _v2;};
        std::vector<int> getTrigList() const { return _trig_list ;};
    };
}
#endif