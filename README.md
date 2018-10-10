# Game-Engine

The Active-Dev branch is used mainly for transferring between work spaces or saving between sessions. Commit messages will be frequently
omitted until a stage is ready to be pushed to the Test branch. When the Test branch has enough relevant updates and has been thoroghly
tested, it is ready to be pushed to the master branch.

The goal of this was to make it able to run on its own without the need for dependencies. The only requirement is to have DirectX installed
on the operating machine. Once the project has been downloaded, follow these steps to get it running.

1. Open the program and build - Should receive an error message that "assimp.dll could not be found"
2. Navigate to AssimpLoader Directory (..\Game Engine\Main\WindowManager\System\Entity\Model\AssimpLoader\Directories)
3. Choose the correct bin for your OS (32 or 64 bit) and open the folder
4. Copy assimp.dll
5. Return to the base directory of the hierarchy (..\Game Engine)
6. Open the x64 or x86 folder and the debug folder within it
7. Paste assimp.dll in this debug folder