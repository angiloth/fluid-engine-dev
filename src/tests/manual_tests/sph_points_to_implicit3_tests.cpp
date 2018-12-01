// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#include <manual_tests.h>

#include <jet/marching_cubes.h>
#include <jet/sph_points_to_implicit3.h>
#include <jet/vertex_centered_scalar_grid.h>

#include <random>

using namespace jet;

JET_TESTS(SphPointsToImplicit3);

JET_BEGIN_TEST_F(SphPointsToImplicit3, ConvertTwo) {
    Array1<Vector3D> points;

    std::mt19937 rng{0};
    std::uniform_real_distribution<> dist(0.2, 0.8);
    for (size_t i = 0; i < 2; ++i) {
        points.append(Vector3D{dist(rng), dist(rng), dist(rng)});
    }

    VertexCenteredScalarGrid3 grid({128, 128, 128},
                                   {1.0 / 128, 1.0 / 128, 1.0 / 128});

    SphPointsToImplicit3 converter(0.3);
    converter.convert(points.view(), &grid);

    TriangleMesh3 triMesh;
    marchingCubes(grid.dataView(), grid.gridSpacing(), grid.dataOrigin(),
                  &triMesh, 0, kDirectionAll);

    saveTriangleMeshData(triMesh, "sph_points_to_implicit3_convert_two.obj");
}
JET_END_TEST_F

JET_BEGIN_TEST_F(SphPointsToImplicit3, ConvertMany) {
    Array1<Vector3D> points;

    std::mt19937 rng{0};
    std::uniform_real_distribution<> dist(0.2, 0.8);
    for (size_t i = 0; i < 500; ++i) {
        points.append(Vector3D{dist(rng), dist(rng), dist(rng)});
    }

    VertexCenteredScalarGrid3 grid({128, 128, 128},
                                   {1.0 / 128, 1.0 / 128, 1.0 / 128});

    SphPointsToImplicit3 converter(0.1);
    converter.convert(points.view(), &grid);

    TriangleMesh3 triMesh;
    marchingCubes(grid.dataView(), grid.gridSpacing(), grid.dataOrigin(),
                  &triMesh, 0, kDirectionAll);

    saveTriangleMeshData(triMesh, "sph_points_to_implicit3_convert_many.obj");
}
JET_END_TEST_F
