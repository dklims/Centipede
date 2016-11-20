REM Visual Studio project Clean Up
REM Andre Berthiaume, April 2013 (Improved from Ed Keenan's original)

REM Assign PNAME with the name of the .sln file
for %%* in (*.sln) do set PNAME=%%~n*

REM Delete all the unneeded stuff
rmdir /S /Q Debug
rmdir /S /Q ipch
rmdir /S /Q Release
del /F /S "%PNAME%.sdf"
del /F /S "%PNAME%.opensdf"
del /F /S /AH "%PNAME%.suo"
del /F /S /AH "%PNAME%.v11.suo"
del /F /S /AH "%PNAME%.v12.suo"
rmdir /S /Q "%PNAME%\Debug"
rmdir /S /Q "%PNAME%\Release"
del /F /S *.db
