echo Post Build for DEBUG VERSION

U:\ProjEnv\SoftIce95\nmsym.exe /TRANSLATE:PACKAGE,ALWAYS,SOURCE /SOURCE:. /OUTPUT:.\debug\app.nms .\debug\sample99.exe

copy .\Debug\sample99.exe .\..\..\tools\Backward\init32.exe
