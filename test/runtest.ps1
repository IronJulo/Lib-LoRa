$env:GTEST_COLOR=1
$env:TERM="xterm-color"
$env:CLICOLOR_FORCE=1
cmake -S . -B build
cmake --build build
#cd .\build\test\
ctest -V --test-dir build\test --output-on-failure -j12
#ctest -V | Write-Host
#$testOutput = ctest --gtest_color=yes -V | Out-String
#Write-Host $( [char]27) $testOutput $( [char]27)
#cd ..
#cd ..
#.\build\test\Debug\TestExecutable.exe