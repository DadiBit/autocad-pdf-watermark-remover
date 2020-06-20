@echo off
set /p "file=File name: "
for /f "delims=" %%f in ("%file%") do (
    set "file.fullpath=%%~ff"
    set "file.size=%%~zf"
    set "file.path=%%~dpf"
    set "file.name=%%~nf"
    set "file.extension=%%~xf"
)
cd %~dp0
if /i "%file.extension%" == ".pdf" (
    pdftk %file.fullpath% output %file.path%%file.name%_uncompressed.pdf uncompress
    rmwm %file.path%%file.name%_uncompressed.pdf %file.path%%file.name%_uncompressed_nowatermark.pdf
    pdftk %file.path%%file.name%_uncompressed_nowatermark.pdf output %file.path%%file.name%_nowatermark.pdf compress

) else (
    echo %file.extension% Use a .pdf file
)
pause