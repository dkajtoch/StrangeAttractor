#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <stdio.h>

class ProgressIndicator {

public:

    ProgressIndicator(std::size_t start, std::size_t stop, std::size_t n)
        : start{start}, stop{stop}, n{n}
    {
        step = static_cast<std::size_t>(
            (static_cast<double>(stop)-static_cast<double>(start))/
            static_cast<double>(n));
    }

    void update(std::size_t i) const
    {
        if( i % step == 0 )
        {
            double progress = static_cast<double>(i)/
                (static_cast<double>(stop)-static_cast<double>(start))
                 * 100.0;
            printf("\r[=> %.2f %%", progress);
            fflush(stdout);
        }
        if( i == stop )
            printf("\r[=> 100.00 %%\n");
    }

    std::size_t start, stop, n;

private:

    std::size_t step;
};

#endif
