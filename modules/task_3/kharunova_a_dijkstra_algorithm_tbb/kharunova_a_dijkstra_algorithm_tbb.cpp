// Copyright 2022 Kharunova Alina
#include <tbb/tbb.h>
#include <vector>
#include <random>
#include <iostream>
#include "../../../modules/task_3/kharunova_a_dijkstra_algorithm_tbb/kharunova_a_dijkstra_algorithm_tbb.h"

#define THREADS 4

std::vector<std::vector<int>> create_random_graph(int num_of_vertex,
                                                  int max_destination) {
  if (num_of_vertex <= 0) {
    throw "Wrong number of vertexes";
  }
  std::vector<std::vector<int>> matrix_of_connection(
      num_of_vertex, std::vector<int>(num_of_vertex, 0));
  std::random_device dev;
  std::mt19937 gen(dev());
  int startCol = 0, destination = 0, row, col;
    for (row = 0; row < num_of_vertex; row++) {
      for (col = startCol; col < num_of_vertex; col++) {
        if (row != col) {
          destination = dev() % max_destination;
          matrix_of_connection[row][col] = destination;
          matrix_of_connection[col][row] = destination;
        }
      }
      startCol++;
    }
  return matrix_of_connection;
}

void start_parallel_algorithm(int num_of_vertex,
                              int max_destination) {
  if (num_of_vertex <= 0) {
    throw("Wrong number of vertexes");
  }
  if (max_destination <= 0) {
    throw("Wrong value of maximum destination");
  }

  struct Minimum {
    int min_dest;
    int last_index;
  };
  std::vector<int> min_destinations(num_of_vertex, 10000);
  std::vector<int> passed_vertexes(num_of_vertex, 0);
  std::vector<std::vector<int>> matrix_of_connections =
      create_random_graph(num_of_vertex, max_destination);

  min_destinations[0] = 0;

  Minimum general;
  general.last_index = 10000;

  int grainsize = num_of_vertex / THREADS;
  tbb::task_scheduler_init init(THREADS);

  for (int i = 0; i < num_of_vertex; i++) {
    general.min_dest = 10000;

    general = tbb::parallel_reduce(
        tbb::blocked_range<int>(0, num_of_vertex, grainsize), general,
        [&](const tbb::blocked_range<int>& range, Minimum local) {
          for (int j = range.begin(); j < range.end(); j++) {
            if (!passed_vertexes[j] && min_destinations[j] < local.min_dest) {
              local.min_dest = min_destinations[j];
              local.last_index = j;
            }
          }
          return local;
        },
        [](Minimum first, Minimum second) {
          if (first.min_dest < second.min_dest)
            return first;
          return second;
        });

    passed_vertexes[general.last_index] = 1;

    tbb::parallel_for(
        tbb::blocked_range<int>(0, num_of_vertex, grainsize),
        [&](const tbb::blocked_range<int>& range) {
          for (int k = range.begin(); k < range.end(); k++) {
            if (!passed_vertexes[k] &&
                min_destinations[general.last_index] != 10000 &&
                matrix_of_connections[general.last_index][k] &&
                min_destinations[general.last_index] +
                        matrix_of_connections[general.last_index][k] <
                    min_destinations[k]) {
              min_destinations[k] = min_destinations[general.last_index] +
                        matrix_of_connections[general.last_index][k];
            }
          }
        });
  }

  std::vector<int> shortest_path;
  int end_vertex = num_of_vertex - 1;
  shortest_path.push_back(end_vertex);
  int weight_of_end_vertex = min_destinations[end_vertex],
      weight_of_last_vertex;

  while (end_vertex != 0) {
      for (int i = 0; i < num_of_vertex; i++) {
        if (matrix_of_connections[i][end_vertex] != 0) {
          weight_of_last_vertex =
              weight_of_end_vertex - matrix_of_connections[i][end_vertex];
          if (weight_of_last_vertex == min_destinations[i]) {
            weight_of_end_vertex = weight_of_last_vertex;
            end_vertex = i;
            shortest_path.push_back(i);
          }
        }
      }
    }
}
