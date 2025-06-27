/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    testMesh

Description
    A simple utility for testing the functionality of the OpenFOAM mesh.

Author
   Philip Cardiff

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"

    Info<< "Number of cells = " << mesh.nCells() << nl
        << "Number of faces = " << mesh.nFaces() << nl
        << "Number of points = " << mesh.nPoints() << endl;

    // Info<< "Points[0] = " << mesh.points()[0] << endl;
    // Info<< "faces = " << mesh.faces() << endl;

    const pointField& points = mesh.points();
    const faceList& faces = mesh.faces();

    const face& face0 = faces[0];

    forAll(face0, i)
    {
        Info<< "i = " << i << nl
            << "    face0[" << i << "] = " << face0[i] << endl;

        const label pointID = face0[i];

        Info<< "    points[" << pointID << "] = " << points[pointID] << endl;
    }

    // Info<< "Mesh.cells() = " << mesh.cells() << endl;

    const cell& cell0 = mesh.cells()[0];

    forAll(cell0, fI)
    {
        const label faceID = cell0[fI];
        Info<< "fI = " << fI << nl
            << "    faceID = " << faceID << endl;

        const face& curFace = faces[faceID];

        forAll(curFace, pI)
        {
            const label pointID = curFace[pI];
            Info<< "        p = " << points[pointID] << endl;
        }
    }

    Info<< "cellCells[0] " << mesh.cellCells()[0] << endl;

    Info<< "mesh.C()[0] " << mesh.C()[0] << nl
        << "mesh.V()[0] " << mesh.V()[0] << endl;

    mesh.checkMesh(true);

    // Copy the points
    pointField newPoints(mesh.points());

    // Add a perturbation to the points
    const scalar A = 0.05;
    const scalar B = 4;
    const scalarField x(mesh.points().component(vector::X));
    newPoints += A*Foam::sin(B*constant::mathematical::pi*x)*vector(1, 0, 0);

    runTime++;
    mesh.movePoints(newPoints);
    mesh.write();

    runTime.printExecutionTime(Info);

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
