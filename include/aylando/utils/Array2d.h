#include <array>
#include <algorithm>

namespace aylando::utils
{
    template <typename T, int WIDTH, int HEIGHT>
    struct Array2d
    {
        using type = Array2d<T, WIDTH, HEIGHT>;
        constexpr static auto width = WIDTH;
        constexpr static auto height = HEIGHT;

        T& operator()(int x, int y)
        {
            return arr[x + y * width];
        }

        auto begin()
        {
            return arr.begin();
        }
        auto begin() const
        {
            return arr.begin();
        }

        auto end()
        {
            return arr.end();
        }
        auto end() const
        {
            return arr.end();
        }

    private:
        std::array<T, width * height> arr;
    };

    template <typename T, int WIDTH, int HEIGHT>
    void reset(Array2d<T, WIDTH, HEIGHT>& arr, const T& t = T{})
    {
        std::fill(std::begin(arr), std::end(arr), t);
    }

}