Info<< "Reading field T\n" << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading c (speed of sound)\n" << endl;


IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar c("c", dimVelocity, transportProperties);
dimensionedScalar cSquared = sqr(c);

if (c.value() < SMALL)
{
    FatalError
        << "c should be positive!" << abort(FatalError);
}
else if (c.value() > 1e15)
{
    Warning
        << "c seems a bit large!" << endl;
}
else
{
    Info<< "c = " << c.value() << endl;
}

Switch implicit(transportProperties.lookup("implicit"));
