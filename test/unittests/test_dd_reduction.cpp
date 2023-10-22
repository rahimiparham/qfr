#include "CircuitOptimizer.hpp"
#include "QuantumComputation.hpp"
#include "dd/FunctionalityConstruction.hpp"
#include "dd/Simulation.hpp"
#include "dd/Export.hpp"
#include "dd/Edge.hpp"

#include "gtest/gtest.h"

TEST(DDReduceOperator, DDReduceTranspose_Test1) {
    // Unitary matrix
    const auto inputMatrix = dd::CMat {{dd::SQRT2_2, dd::SQRT2_2, 0, 0},
                                        {-dd::SQRT2_2, dd::SQRT2_2, 0, 0},
                                        {0, 0, dd::SQRT2_2, -dd::SQRT2_2},
                                        {0, 0, dd::SQRT2_2, dd::SQRT2_2}};

    // const dd::QubitCount nrQubits = 2;
    std::size_t nrQubits = 2;
    const auto ddo = std::make_unique<dd::Package<>>(nrQubits);

    dd::mEdge regular_dd = ddo->makeDDFromMatrix(inputMatrix);
    auto regular_matrix = ddo->getMatrix(regular_dd);
    EXPECT_EQ(inputMatrix, regular_matrix);

    // ddo->setTransposedPointer(regular_dd);

    // ddo->setRegularPointer(regular_dd);

    regular_matrix = ddo->getMatrix(regular_dd);
    EXPECT_EQ(inputMatrix, regular_matrix);

    const auto reduced_dd = ddo->reduceEdgeOperation(regular_dd, 1);

    auto reduced_dd_matrix = ddo->getMatrix(reduced_dd);
    EXPECT_EQ(inputMatrix, reduced_dd_matrix);
    
    ddo->setRegularPointer(reduced_dd.p->e[0]);
    ddo->setRegularPointer(reduced_dd.p->e[1]);
    ddo->setRegularPointer(reduced_dd.p->e[2]);
    ddo->setRegularPointer(reduced_dd.p->e[3]);
    ddo->setRegularPointer(reduced_dd.p->e[0].p->e[0]);
    ddo->setRegularPointer(reduced_dd.p->e[0].p->e[1]);
    ddo->setRegularPointer(reduced_dd.p->e[0].p->e[2]);
    ddo->setRegularPointer(reduced_dd.p->e[0].p->e[3]);
    ddo->setRegularPointer(reduced_dd.p->e[3].p->e[0]);
    ddo->setRegularPointer(reduced_dd.p->e[3].p->e[1]);
    ddo->setRegularPointer(reduced_dd.p->e[3].p->e[2]);
    ddo->setRegularPointer(reduced_dd.p->e[3].p->e[3]);

    auto num_nodes_reduced_dd = ddo->size(reduced_dd);

    EXPECT_EQ(3, num_nodes_reduced_dd);

    // std::ostringstream oss{};
    // std::string reduced_dd_goal = "1\n0.70710678118654757\n0 0 (-1 1) (-1 -1) (-1 1) (-1 1)\n1 1 (0 1T) () () (0 1)\n";
    // dd::serialize(reduced_dd, oss, false);
    // auto serialized_reduced_dd = oss.str();
    // // std::cout << "serialized reduced dd:" << std::endl << serialized_reduced_dd;
    // EXPECT_EQ(reduced_dd_goal, serialized_reduced_dd);

    // std::cout << "-----------------------------" << std::endl;

}

TEST(DDReduceOperator, DDReduceX_Test1) {
    // Unitary matrix
    const auto inputMatrix = dd::CMat {{dd::SQRT2_2, dd::SQRT2_2, 0, 0},
                                        {-dd::SQRT2_2, dd::SQRT2_2, 0, 0},
                                        {0, 0, dd::SQRT2_2, -dd::SQRT2_2},
                                        {0, 0, dd::SQRT2_2, dd::SQRT2_2}};

    // const dd::QubitCount nrQubits = 2;
    std::size_t nrQubits = 2;
    const auto ddo = std::make_unique<dd::Package<>>(nrQubits);

    dd::mEdge regular_dd = ddo->makeDDFromMatrix(inputMatrix);
    // std::cout << "-----------------------------" << std::endl;
    // std::cout << "redconstructed matrix of regular dd:" << std::endl;
    // ddo->printMatrix(regular_dd);
    // std::cout << std::endl;
    auto regular_matrix = ddo->getMatrix(regular_dd);
    EXPECT_EQ(inputMatrix, regular_matrix);

    const auto reduced_dd = ddo->reduceEdgeOperation(regular_dd, 3);
    // TODO: extend other print mat function in package class
    // std::cout << "redconstructed matrix of reduced dd:" << std::endl;
    // ddo->printMatrix(reduced_dd);
    // std::cout << std::endl;
    auto reduced_dd_matrix = ddo->getMatrix(reduced_dd);
    EXPECT_EQ(inputMatrix, reduced_dd_matrix);

    // std::cout << "-----------------------------" << std::endl;
}