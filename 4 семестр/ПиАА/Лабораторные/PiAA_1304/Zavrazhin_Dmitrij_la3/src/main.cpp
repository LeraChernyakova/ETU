/** @file */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

/** 'DISCONNECTED' corresponds to a weight of infinity. */
constexpr unsigned DISCONNECTED = 1 << 18;

/**
 * 'TripPlanner' encapsulates the logic of finding a circuit to the travelling
 * salesman problem (TSP) using an approach based on the Bellman-Held-Karp
 * algorithm. It reads the required data from stdin.
 */
class TripPlanner
{
private:
   /**
    * 'Map' is an auxiliary class used to represent a bipartite graph with
    * weighed edged.
    */
   class Map
   {
   public:
       /** A type to denote a number ov verrtices. */
      using Cardinality = unsigned;
      /** A type to denote a vertex as an index. */
      using Vertex = unsigned;
      /** A type to represent a weight of a given edge. */
      using Weight = unsigned;

      /** The number of vertices in the first part. */
      const Cardinality cardinality;
      /** The number of vertices in the first part. */
      const Cardinality second_cardinality;
   private:
      /** The vector of weights associated with vertices. */
      std::vector<Weight> weights;

   public:
      /**
       * This constructor constructs an empty object.
       */
      Map() : Map(0) { }

      /**
       * The constructor with one parameter constructs a graph with n x n
       * potential edges.
       *
       * \param cardinality The number of nodes in the graph.
       */
      Map(Cardinality cardinality)
      : cardinality{cardinality}
      , second_cardinality{cardinality}
      , weights(cardinality * cardinality, DISCONNECTED) { }

      /**
       * The constructor with both parameter constructs a bipartite graph
       * with n x m potential edges.
       *
       * @param cardinality The number of nodes in the graph.
       * @param second_cardinality The number of nodes in the graph.
       */
      Map(Cardinality cardinality, Cardinality second_cardinality)
      : cardinality{cardinality}
      , second_cardinality{second_cardinality}
      , weights(cardinality * second_cardinality, DISCONNECTED) { }

      /**
       * The copy constructor copies the graph.
       *
       * @param map The graph to be copied.
       */
      Map(const Map &map)
      : cardinality{map.cardinality}
      , second_cardinality{map.second_cardinality}
      , weights{map.weights} { }

      /**
       * The assignment operator copies the graph.
       *
       * @param map The graph to be copied.
       * @returns Pointer to the created copy.
       */
      Map &operator=(const Map &map)
      {  if(this == &map)
         {  return *this;  }
         this->~Map();
         return *new(this) Map(map);
      }

      /**
       * 'get_weight' is a getter for a weight associated with a given edge.
       *
       * @param x The first vertex of the edge.
       * @param y The second vertex of the edge.
       * @returns A weight associated with the specified vertex.
       */
      Weight get_weight(Vertex i, Vertex j) const
      {  return this->weights[i * this->cardinality + j];  }

      /**
       * 'get_weight' is a getter/setter for a weight associated with a given
       * edge.
       *
       * @param x The first vertex of the edge.
       * @param y The second vertex of the edge.
       * @returns A reight associated with the specified vertex.
       */
      Weight &get_weight(Vertex i, Vertex j)
      {  return this->weights[i * this->cardinality + j];  }
   };

   /** A variable to hold a given graph. */
   Map map;
   /** A variable to hopefully hold a correct circuit. */
   std::vector<Map::Vertex> circuit;
   /** A variable to hopefully hold the weight of a correct circuit. */
   Map::Weight circuit_weight = DISCONNECTED;
   /** A variable for code benchmarking. */
   std::chrono::nanoseconds benchmark;
   
   /** A type to represent a permutation of vertices. */
   // It would be nice to have a class instead, but all the hassle with pointers
   // significantly decreases performance (about 1.5 seconds for n = 20,
   // rendom weights).
   using Subset = unsigned long long;

   /**
    * 'arity' determines the number of elements in a given permutation.
    *
    * @param permutation A permutation to find the arity of.
    * @returns Arity of the given permutation.
    */
   Map::Cardinality arity(Subset subset) const
   {  Map::Cardinality arity = 0;
      for (; subset; arity++)
      {  subset &= subset - 1;  }
      return arity;
   }

   #define SUBSET

   /**
    * 'use_bellman_held_karp_algorithm' uses the Bellman-Held-Karp algorithm
    * to solve the travelling salesman problem in exponential time, but with
    * higher memory requirements.
    */
   void use_bellman_held_karp_algorithm()
   {
      const Map::Cardinality variable_vertex_count = this->map.cardinality - 1;
      Subset set = (1 << variable_vertex_count) - 1;
      Map paths(variable_vertex_count, set + 1);
      std::map<std::pair<Subset, Map::Vertex>, Map::Vertex> tags;
      constexpr Map::Vertex FIXED_VERTEX = 0, SECOND_VERTEX = 0;

      for(Map::Vertex i = SECOND_VERTEX; i < variable_vertex_count; ++i)
      {  paths.get_weight(1 << i, i) = this->map.get_weight(FIXED_VERTEX, i + 1);  }
      for(Map::Cardinality arity = 2; arity <= variable_vertex_count; arity++)
      {  for (Subset subset = 1; subset <= set; ++subset)
         {  if(this->arity(subset) != arity)
            {  continue;  }
            for (Map::Vertex i = SECOND_VERTEX; i < variable_vertex_count; ++i)
            {  if(not (subset & 1 << i))
               {  continue;  }
               Subset previous = subset ^ 1 << i; 
               for (Map::Vertex j = SECOND_VERTEX; j < variable_vertex_count; ++j)
               {  if(not (subset & 1 << j))
                  {  continue;  }
                  Map::Weight weight = paths.get_weight(previous, j);
                  weight += this->map.get_weight(j + 1, i + 1);
                  if(weight < paths.get_weight(subset, i))
                  {  paths.get_weight(subset, i) = weight;
                     tags[{subset, i}] = j + 1;
      }  }  }  }  }
     
      this->circuit_weight = DISCONNECTED;
      Map::Vertex vertex = 0;
      for(int i = FIXED_VERTEX; i < variable_vertex_count; ++i)
      {  Map::Weight weight = paths.get_weight(set, i);
         weight += this->map.get_weight(i + 1, FIXED_VERTEX);
         if(this->circuit_weight > weight)
         {  this->circuit_weight = weight;
            vertex = i;
      }  }
      if(this->circuit_weight == DISCONNECTED)
      {  return;  }

      this->circuit.clear();
      this->circuit.insert(circuit.end(), {FIXED_VERTEX, vertex + 1});
      while(this->arity(set) != 0)
      {  this->circuit.push_back(tags[{set, vertex}]);
         Map::Vertex next_vertex = vertex;
         vertex = tags[{set, vertex}] - 1;
         set ^= 1 << next_vertex;
      }
      std::reverse(this->circuit.begin(), this->circuit.end());
   }

public:
   /**
    * The constructor reads the required data from stdin and initialises the
    * graph accordingly.
    */
   TripPlanner()
   {  unsigned cardinality;
      std::cin >> cardinality;
      this->map = Map(cardinality);

      constexpr unsigned MIN_WEIGHT = 1;
      constexpr unsigned MAX_WEIGHT = 1000;
      for(unsigned i = 0; i < cardinality; ++i)
      {  for(unsigned j = 0; j < cardinality; ++j)
         {  std::cin >> this->map.get_weight(i, j);  
            if(this->map.get_weight(i, j) < MIN_WEIGHT or
               MAX_WEIGHT < this->map.get_weight(i, j))
            {  this->map.get_weight(i, j) = DISCONNECTED;  }
   }  }  }

   /**
    * 'plan' calls the implemented algorithm and benchmarks it.
    */
   TripPlanner &plan()
   {  if(this->map.cardinality == 0)
      {  return *this;  }
      auto begin = std::chrono::high_resolution_clock::now();
      this->use_bellman_held_karp_algorithm();
      auto time = std::chrono::high_resolution_clock::now() - begin;
      this->benchmark = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
      return *this;
   }

   friend std::ostream &operator<<(std::ostream &out, const TripPlanner &planner);
};

/**
 * The overloaded operator is used to output a circuit.
 */
std::ostream &operator<<(std::ostream &out, const TripPlanner &planner)
{  if(planner.circuit.size() == 0)
   {  out << "[], ";  }
   else
   {  out << '[' << planner.circuit[0] + 1;
      for(int i = 1; i < planner.circuit.size(); i++)
      {  out << ", " << planner.circuit[i] + 1;  }
      out << "], ";
   }
   if(planner.circuit_weight == DISCONNECTED)
   {  out << "No path exists";  }
   else
   {  out << planner.circuit_weight;  }
   return out << ", " << planner.benchmark.count() << "ns";
}

int main()
{  return std::cout << TripPlanner().plan() << std::endl, 0;  }

