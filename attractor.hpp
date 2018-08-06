#ifndef _ATTRACTOR_HPP_
#define _ATTRACTOR_HPP_

#include <vector>
#include <array>
#include <map>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>

class Attractor {

public:
    // leaves domain boundary to default
    Attractor(int width, int height)
        : n_cols{width}, n_rows{height}
    {}

   // constructor with user defined domain boundary
   Attractor(int width, int height, std::map<std::string,double> edges)
      : n_cols{width}, n_rows{height}, xmin{edges["xmin"]}, xmax{edges["xmax"]},
        ymin{edges["ymin"]}, ymax{edges["ymax"]}
   {}

   // run iteration at least fixed number of seconds specified
   // by the parameter 'seconds'
    void run(std::array<double,2> start, double seconds)
    {
        double x = start[0];
        double y = start[1];

        std::size_t xint, yint;

        freq = std::vector<double>(n_rows * n_cols);

        //auto bar = ProgressIndicator(0, n_iter-1, 100);
        std::cout << "Setting counter to: " << seconds << "s" << std::endl;

        auto time_start = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds;

        while( elapsed_seconds.count() < seconds )
        {
            for( std::size_t i=0; i<1000; i++)
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

               //bar.update(i);
            }

            auto time_end = std::chrono::system_clock::now();
            elapsed_seconds = time_end-time_start;
        }

        // find maximum and normalize
        double maxval = *std::max_element(freq.begin(), freq.end());
        for(auto it=freq.begin(); it != freq.end(); it++)
        {
            // penalize unvisited points
            *it = *it/maxval;
            /*if(*it == 0.0)
                *it = -1.0;
            else
                *it = *it/maxval;
            */
        }
    }

    void data_export(std::string filename)
    {
        std::ofstream file(filename, std::ios::binary);

        if(file.is_open())
        {
            std::cout << "Writing in progress..." << std::endl;

            // header
            file << n_cols << " "; // width
            file << n_rows << "\n"; // height

            float cast;
            for(auto x: freq)
            {
                cast = static_cast<float>(x);
                file.write(reinterpret_cast<char*>(&cast), sizeof(cast));
            }
            file.close();
        }
        else
            std::cout << "Unable to open the file!" << std::endl;
    }

    // export data to a simple graphics in grayscale PGM
    // precision: "8bit" - 0-255 coding values
    //            "16bit" - 0-65535 coding value
    void pgm_export(std::string filename, std::string precision)
    {
        if( precision == std::string("8bit") )
        {
            filename += std::string("8bit");
            filename += std::string(".pgm");
            std::ofstream file(filename, std::ios::binary);

            if(file.is_open())
            {
                std::cout << "Writing in progress..." << std::endl;

                // header
                file << "P5" << " ";
                file << n_cols << " "; // width
                file << n_rows << " "; // height
                file << UINT8_MAX << "\n"; // max number

                for(auto x: freq)
                    file << static_cast<uint8_t>( x * UINT8_MAX );

                file.close();
            }
            else
                throw("Unable to open the file!");
        }
        else if( precision == std::string("16bit") )
        {
            filename += std::string("16bit");
            filename += std::string(".pgm");
            std::ofstream file(filename, std::ios::binary);

            if(file.is_open())
            {
                std::cout << "Writing in progress..." << std::endl;

                // header
                file << "P5" << " ";
                file << n_cols << " "; // width
                file << n_rows << " "; // height
                file << UINT16_MAX << "\n"; // max number

                uint16_t cast;
                for(auto x: freq)
                {
                    cast = static_cast<uint16_t>( x * UINT16_MAX );
                    file.write(reinterpret_cast<char*>(&cast), sizeof(cast));
                }
                file.close();
            }
            else
                throw("Unable to open the file!");
        }
        else
            throw("Unrecognized precision format!");
    }

    // pure virtual
    virtual void iter(double& x, double& y) = 0;

    int n_cols;
    int n_rows;
    std::vector<double> freq;

protected:

    double xmin;
    double xmax;
    double ymin;
    double ymax;
};

/* ----------------------------------- /
/ Cliford attractor definition         /
/ ----------------------------------- */
class Clifford: public Attractor {

public:

   // delete default constructor
   Clifford() = delete;

   // constructor with default domain boundary
   Clifford(std::array<double,4> param, int width, int height)
      : Attractor(width, height), a{param[0]}, b{param[1]},
        c{param[2]}, d{param[3]}
   {
      xmax = 1.0 + std::abs(c);
      xmin = -xmax;
      ymax = 1.0 + std::abs(d);
      ymin = -ymax;
   }

   // constructor with user-defined domain boundary
   Clifford(std::array<double,4> param, int width, int height,
            std::map<std::string,double> edges)
      : Attractor(width, height, edges), a{param[0]}, b{param[1]},
        c{param[2]}, d{param[3]}
   {}

   void iter(double& x, double& y)
   {
       double xx = x;
       x = c * std::cos( a * x ) + std::sin( a * y );
       y = d * std::cos( b * y ) + std::sin( b * xx );
   }

private:

   double a, b, c, d;
};

/* ----------------------------------- /
/ Peter DeJong attractor definition    /
/ ----------------------------------- */
class PeterDeJong: public Attractor {

public:
   // delete default constructor
   PeterDeJong() = delete;

    // constructor with default domain boundary
    PeterDeJong(std::array<double,4> param, int width, int height)
        : Attractor(width, height), a{param[0]}, b{param[1]},
          c{param[2]}, d{param[3]}
     {
         xmax = 2.0;
         xmin = -xmax;
         ymax = 2.0;
         ymin = -ymax;
    }

    // constructor with user-defined domain boundary
    PeterDeJong(std::array<double,4> param, int width, int height,
                std::map<std::string,double> edges)
        : Attractor(width, height, edges), a{param[0]}, b{param[1]},
          c{param[2]}, d{param[3]}
   {}

    void iter(double& x, double& y)
    {
        double xx = x;
        x = std::sin( a * y ) - std::cos( b * x );
        y = std::sin( c * xx ) - std::cos( d * y );
    }

 private:

    double a, b, c, d;
};

/* ----------------------------------- /
/ Bedhead attractor definition         /
/ ----------------------------------- */
class Bedhead: public Attractor {

public:

   // default constructor
   Bedhead() = delete;

   // default domain boundary (loosely defined)
   Bedhead(std::array<double,2> param, int width, int height)
      : Attractor(width, height), a{param[0]}, b{param[1]}
   {
      xmin = -4.0;
      xmax = 4.0;
      ymin = -4.0;
      ymax = 4.0;
   }

   // uder defined domain
   Bedhead(std::array<double,2> param, int width, int height,
      std::map<std::string, double> edges)
      : Attractor(width, height, edges), a{param[0]}, b{param[1]}
   {}

   void iter(double& x, double& y)
   {
      double xx = x;
      x = std::sin( x * y / b) * y + std::cos( a * x - y );
      y = xx + std::sin( y ) / b;
   }

private:

   double a, b;
};

#endif
