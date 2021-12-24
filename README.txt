# LastCollisionBug
Example project to show a bug such that clearing a mesh section of a ProceduralMeshComponent(PMC) doesn't remove last mesh collision if bUseAsyncCooking=true.
This is made with UE 4.27.2.

## Usage
Click your left mouse button to make/clear a box mesh.
If you move your character towards the position where the mesh was, you still collide with it even though mesh is removed. Last collision won't be removed after clearing a section if bUseAsyncCooking=true.

This project also include an actor on the main level to test the bug with Runtime Mesh Component(RMC), which is a plugin available for free on the marketplace.
This actor has a component that calculates mesh/collision data at runtime on other thread. When clearing a mesh, it just return false in IInterface_CollisionDataProvider::ContainsPhysicsTriMeshData function.

## Easiest solution, and why this bug should be fixed.
If you use PMC, super easy. The mesh calculation is done on main thread, so you can just use SetCollisionEnabled to disable collision after the calculation.
However, this temporary fix won't be easy for a project which calculates mesh data on other therad, such as RMC, because it is hard to call actor's function from other thread.
For example, you may want to calculate mesh with noise function on other thread. In this case, a class which calculates mesh on other thead can know if it actually has a valid mesh data, but it is difficult for him to access to game thread functions.

## Some sfuff I found
If bUseAsyncCooking=false in Procedural Mesh Component, then it is totally fine. Try toggling BP_MyRuntimeMesh's CollisionSettings > bUseAsyncCooking as well.

If you open BP_PMCMesh and set a variable bAlwaysCookPhysics to true, then IInterface_CollisionDataProvider::ContainsPhysicsTriMeshData will always return true. That will clear collision well but it makes a warning "LogPhysics: Warning: UBodySetup::GetCookInfo: Triangle data from '/Game/ThirdPersonCPP/Maps/UEDPIE_0_ThirdPersonExampleMap.ThirdPersonExampleMap:PersistentLevel.BP_PMCMesh_2.ProceduralMesh' invalid (0 verts, 0 indices)."