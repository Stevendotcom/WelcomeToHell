@echo off

echo %1 Solution Dir
echo %2 Target Dir
echo "%3" Target Name
echo "%4" Lib Name

if "%5"=="1" (
    echo Copying and packing
    del "%~1bin\Release\%~3.pdb"
    xcopy "%~1res" "%~2res" /i /y /s
    xcopy "%~1lib\%~4\*" "%~2lib" /i /y /s
    tar --create --file="%~3.zip" -C "%~1bin\Release" .
) ELSE (
xcopy "%~1res" "%~2res" /i /y /s
xcopy "%~1lib\%~4\*" "%~2lib" /i /y /s
)