add_library(myg2o vertex.cc
                  edge.cc)

target_link_libraries(myg2o Eigen3::Eigen)