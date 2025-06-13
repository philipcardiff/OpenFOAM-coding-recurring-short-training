/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2025 AUTHOR,AFFILIATION
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

Class
    Foam::diffusivityLaw

Description
    Custom class for calculating and returning a diffusivity field

SourceFiles
    diffusivityLaw.C

Author
    Philip Cardiff, UCD.

\*---------------------------------------------------------------------------*/

#ifndef diffusivityLaw_H
#define diffusivityLaw_H

#include "diffusivityLaw.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                         Class diffusivityLaw Declaration
\*---------------------------------------------------------------------------*/

class diffusivityLaw
{
    // Private Data

        //- Diffusivity
        //  DT = A0 + A1*T
        volScalarField DT_;

        //- Coefficients
        dimensionedScalar A0_;
        dimensionedScalar A1_;


    // Private Member Functions

        //- No copy construct
        diffusivityLaw(const diffusivityLaw&) = delete;

        //- No copy assignment
        void operator=(const diffusivityLaw&) = delete;


public:


    // Constructors

        //- Default construct
        diffusivityLaw(const fvMesh& mesh, const word& dictName);


    //- Destructor
    ~diffusivityLaw();


    // Member Functions

        //- Update the DT field
        void update(const volScalarField& T);

        //- Return read-only access to the DT field
        const volScalarField& DT()
        {
            return DT_;
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
