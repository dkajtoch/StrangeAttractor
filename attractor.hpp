#ifndef _ATTRACTOR_HPP_
#define _ATTRACTOR_HPP_

#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
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

class Attractor {

public:
    // constructor
    Attractor(std::size_t width, std::size_t height)
        : n_cols{width}, n_rows{height}
    {}

    void run(std::array<double,2> start, std::size_t n_iter)
    {
        double x = start[0];
        double y = start[1];

        std::size_t xint, yint;

        freq = std::vector<double>(n_rows * n_cols);

        auto bar = ProgressIndicator(0, n_iter-1, 100);

        for( std::size_t i=0; i<n_iter; i++)
        {
            iter(x,y);

            xint = static_cast<std::size_t>( (x-xmin)/(xmax-xmin)*n_cols );
            yint = static_cast<std::size_t>(
                std::abs( (y-ymax)/(ymax-ymin)*n_rows )
            );

            try
            {
                freq.at(xint + yint*n_cols) += 1.0;
            }
            catch(...)
            {};

            bar.update(i);
        }

        // find maximum and normalize
        double maxval = *std::max_element(freq.begin(), freq.end());
        for(auto it=freq.begin(); it != freq.end(); it++)
        {
            // penalize unvisited points
            //*it = *it/maxval;
            if(*it == 0.0)
                *it = -1.0;
            else
                *it = *it/maxval;
        }
    }

    void file_export(std::string filename)
    {
        std::ofstream file(filename);

        if(file.is_open())
        {
            std::cout << "Writing in progress..." << std::endl;
            for(std::size_t i=0; i<n_rows; i++)
            {
                for(std::size_t j=0; j<n_cols; j++)
                {
                    file << freq.at(j + i*n_rows)
                         << " ";
                }
                file << "\n";
            }
            file.close();
        }
        else std::cout << "Unable to open the file!" << std::endl;
    }

    // pure virtual
    virtual void iter(double& x, double& y) = 0;

    std::size_t n_cols;
    std::size_t n_rows;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    std::vector<double> freq;
};

class Clifford: public Attractor {

public:

   // constructor
   Clifford(std::array<double,4> param, std::size_t width, std::size_t height)
      : Attractor(width, height), a{param[0]}, b{param[1]},
        c{param[2]}, d{param[3]}
   {
      xmax = 1.0 + std::abs(c);
      xmin = -xmax;
      ymax = 1.0 + std::abs(d);
      ymin = -ymax;
   }

   void iter(double& x, double& y)
   {
       double xx = x;
       x = c * std::cos( a * x ) + std::sin( a * y );
       y = d * std::cos( b * y ) + std::sin( b * xx );
   }

private:

   double a, b, c, d;
};

class PeterDeJong: public Attractor {

    PeterDeJong(std::array<double,4> param, std::size_t width, std::size_t height)
        : Attractor(width, height), a{param[0]}, b{param[1]},
          c{param[2]}, d{param[3]}
     {
         xmax = 2.0;
         xmin = -xmax;
         ymax = 2.0;
         ymin = -ymax;
    }

    void iter(double& x, double& y)
    {
        double xx = x;
        x = std::sin( a * y ) - std::cos( b * x );
        y = std::sin( c * xx ) - std::cos( d * y );
    }

 private:

    double a, b, c, d;
};

#endif
