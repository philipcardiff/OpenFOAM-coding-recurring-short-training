    if (runTime.writeTime())
    {
        volVectorField gradT(fvc::grad(T));

        runTime.write();
    }
