#include <iostream>
#include <vector>

// Tabletop is a class that encapsulates the logic of finding a minimal
// solution to the "squaring the square" problem and also represents its
// solution after it has been found
class Tabletop
{
private:
   // Surface is a helper class to manage already occupied cells
   class Surface
   {
   // It also holds its side and a number of added squares
   public:
      const unsigned side;
   private:
      std::vector<unsigned> cells;
      unsigned n_squares = 0;

   public:
      // The constructor initialises all cells to 0, meaning vacant
      Surface(unsigned side)
      : side{side}, cells(side * side) { }

      Surface(const Surface &surface)
      : side{surface.side}, cells{surface.cells}, n_squares{surface.n_squares} { }

      Surface &operator=(const Surface &surface)
      {  if(this == &surface)
         {  return *this;  }
         this->~Surface();
         return *new(this) Surface(surface);
      }

      // cardinality() is a getter for the number of added squares
      unsigned cardinality() const
      {  return this->n_squares;  }

      // This is a setter in order to set cardinality of the dummy solution
      // without wastingly appending side*side squares
      void cardinality(unsigned c)
      {  this->n_squares = c;  }

      // at() is a getter for a cell value by its (x, y) coordinates
      const unsigned &at(unsigned x, unsigned y) const
      {  return this->cells[x * this->side + y];  }

      unsigned &at(unsigned x, unsigned y)
      {  return this->cells[x * this->side + y];  }

      // is_vacant() tests for whether the cell is empty or not
      bool is_vacant(unsigned x, unsigned y) const
      {  return this->at(x, y) == 0;  }

      // is_meaningful() tests for whether the cell holds a square side
      // or not
      bool is_meaningful(unsigned x, unsigned y) const
      {  return this->at(x, y) < -1;  }

      // add() adds a square conditionally
      // Returns whether the square was added
      bool add(unsigned x, unsigned y, unsigned side)
      {  for(int i = x; i < x + side; i++)
         {  for (int j = y; j < y + side; j++)
            {  if(not this->is_vacant(i, j))
               {  return false;  }
         }  }
         for(int i = x; i < x + side; ++i)
         {  for(int j = y; j < y + side; ++j)
            {  this->at(i, j) = -1;  }
         }
         this->at(x, y) = side; // a "meaningful" cell
         return ++this->n_squares;
      }

      // empty() empties cells of a square-shaped area
      void empty(unsigned x, unsigned y, unsigned side)
      {  for(int i = x; i < x + side; i++)
         {  for(int j = y; j < y + side; j++)
            {  if(this->is_meaningful(i, j))
               {  --this->n_squares;  }
               this->at(i, j) = 0;
      }  }  }
   };

   Surface surface, solution;
   unsigned factor;

   // Recursively fits a piece using backtracking
   void fit(unsigned x, unsigned y)
   {  if(not surface.is_vacant(x, y))
      {  return this->shift(x, y);  }
      unsigned side = std::min(this->surface.side - x, this->surface.side - y);
      for(; side > 0; --side)
      {  if(this->surface.side < x + side or this->surface.side < y + side)
         {  continue;  }
         if(surface.add(x, y, side))
         {  this->shift(x, y, side);
            this->surface.empty(x, y, side);
   }  }  }

   // Conditionally selects the next square placement
   // The surface is traversed line-by-line
   // Branches are cut if they do not improve the already established solution
   void shift(unsigned x, unsigned y, unsigned shift = 1)
   {  if(this->solution.cardinality() <= this->surface.cardinality())
      {  return;  }
      if(y + shift < this->surface.side)
      {  return this->fit(x, y + shift);  }
      if(x + 1 < this->surface.side)
      {  return this->fit(x + 1, this->surface.side / 2);  }
      this->solution = this->surface;
   }

public:
   // The constructor:
   // (1) Determines whether the square is simply a scaled up version of a
   // smaller one;
   // (2) Initialises the surface and the dummy solution
   Tabletop(unsigned side)
   : surface{0}, solution{0} // these are temporary
   {  this->factor = 1;
      // It's not worth it to iterate over primes instead
      for(unsigned factor = 2; factor <= side / 2; ++factor)
      {  if(side % factor == 0)
         {  this->factor = side / factor;
            side = factor;
            break;
      }  }
      this->surface = this->solution = Surface(side);
      solution.cardinality(side * side); // It is pointless to initialise fully
   }

   // Finds an optimal squaring
   Tabletop &square()
   {  unsigned side = this->surface.side / 2 + this->surface.side % 2;
      surface.add(0, 0, side);
      surface.add(side, 0, this->surface.side - side);
      surface.add(0, side, this->surface.side - side);
      if(this->surface.side == 2)
      {  surface.add(side, side, this->surface.side - side);  }
      else
      {  this->fit(this->surface.side / 2, this->surface.side / 2);
         this->surface = this->solution;
      }
      return *this;
   }

   friend std::ostream &operator<<(std::ostream &, const Tabletop &);
};

// Outputs a solution
std::ostream &operator<<(std::ostream &out, const Tabletop &tabletop)
{  out << tabletop.surface.cardinality() << std::endl;
   for(int i = 0; i < tabletop.surface.side; i++)
   {  for(int j = 0; j < tabletop.surface.side; j++)
      {  if(tabletop.surface.is_meaningful(j, i))
         {  out << i * tabletop.factor + 1 << ' ';
            out << j * tabletop.factor + 1 << ' ';
            out << tabletop.surface.at(j, i) * tabletop.factor << std::endl;
   }  }  }
   return out;
}

int main()
{  unsigned side;
   std::cin >> side;
   std::cout << Tabletop(side).square();
   return 0;
}

