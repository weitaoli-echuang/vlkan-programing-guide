echo "current path"
echo %~dp0
cd %~d0
cd %~dp0\build
rm -r *
rm -r .vs
cmake -G "Visual Studio 14 2015 Win64" ..
