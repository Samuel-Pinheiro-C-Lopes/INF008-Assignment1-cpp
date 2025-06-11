#include<memory>
#include<unordered_map>
#include<vector>

namespace alias {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T, typename G>
    using Map = std::unordered_map<T, G>;

    template<typename T>
    using Vector = std::vector<T>;

    using String = std::string;
}
