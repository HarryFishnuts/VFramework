/******************************************************************************
* <framework.h>
* Bailey Jia-Tao Brown
* 2021
* 
*	Header file for abstract graphics and utilites library
*	Contents:
*		- Header guard
*		- Preprocessor directives
*		- API definition
*		- Includes
*		- Definitions
*		- Structs
*		- Module initialization function
*		- Module termination function
*		- Module threading related functions
*		- Struct creation functions
*		- Struct destruction functions
*		- Struct related functions
*		- Rendering functions
*		- Physics functions
*		- Data related functions
* 
******************************************************************************/

#ifndef __VFRAMEWORK_INCLUDE__
#define __VFRAMEWORK_INCLUDE__

/* PREPROCESSOR DIRECTIVES */
#pragma pack(1)

/* API DEFINITIONS */
#ifdef VFRAMEWORK_EXPORTS
#define VFAPI __declspec(dllexport)
#else
#define VFAPI __declspec(dllimport)
#endif

/* INCLUDES */
#include <graphics.h> /* Graphics library */

/* DEFINITIONS */
#define VF_MAX_CHILDREN 0x10
#define VF_BUFFER_SIZE 0x800
#define VF_PARENT_SEARCH_THRESHOLD 0x20
#define VF_COLLISIONS_MAX 0x10
#define VF_NOPARENT NULL
#define VF_NOENTITY NULL
#define VF_MUTEX_TIMEOUT_INTERVAL 0x100
#define VF_PUSHBACK_MAGNITUDE_MAX 0x20
#define VF_TOURQUE_MIN_VELOCITY 1.5f
#define VF_TOURQUE_MAX 5.0f
#define VF_VECTOR_SIMILARITY_THRESOLD 0.15f
#define VF_POSITION_SIMILARITY 0.03f

#define VF_OBJ_TRANSFORM 0x10
#define VF_OBJ_BOUND 0x20
#define VF_OBJ_PARTICLE 0x30
#define VF_OBJ_ENTITY 0x40

#define VF_BUFF_TRANSFORM 0x100
#define VF_BUFF_BOUND 0x200
#define VF_BUFF_PARTICLE 0x300
#define VF_BUFF_ENTITY 0x400

#define VF_MEMTANK_SIZE 0x1000
#define VF_MEMTANK_EXCESS 0x20
#define VF_MEMTANK_INTERVAL 4
#define VF_MEMTANK_FIELDSIZE (VF_MEMTANK_SIZE / VF_MEMTANK_INTERVAL)

#define VECT(x, y) vfCreateVector(x, y)
#define COLOR(r, g, b) vfCreateColor(r, g, b, 255)
#define PHYS(b, d, m) vfCreatePhysics(b, d, m)
#define PHYSA(b, d, m, mov, rLock) vfCreatePhysicsa(b, d, m, mov, rLock)

/* STRUCTURE DEFINITIONS */
typedef unsigned int vfHandle;
typedef void (*ENTCOLCALLBACK)(struct vfEntity* source, struct vfEntity* target);
typedef void (*ENTUPDCALLBACK)(struct vfEntity* source);

typedef struct vfVector
{
	float x;
	float y;
} vfVector;

typedef struct vfColor
{
	int r;
	int g;
	int b;
	int a;
} vfColor;

typedef struct vfTransform
{
	vfVector position;
	float rotation;
	float scale;

	struct vfTransform* parent;
} vfTransform;

typedef struct vfPhysics
{
	int active;
	int moveable;
	int rotationLock;
	float bounciness;
	float drag;
	float mass;

	vfVector velocity;
	float tourque;
} vfPhysics;

typedef struct vfBound
{
	int active;
	vfTransform* body;
	vfVector position;
	vfVector dimensions;

	struct vfEntity* entity;
} vfBound;

typedef struct vfParticle
{
	int active;
	unsigned char layer;
	vgShape shape;
	vgTexture texture;
	vfColor filter;

	vfTransform* transform;
} vfParticle;

typedef struct vfEntity
{
	int active;
	unsigned char layer;
	vgTexture texture;
	vgShape shape;
	vfColor filter;

	vfBound* bounds;
	vfPhysics physics;
	vfTransform* transform;

	ENTCOLCALLBACK collisionCallback;
	ENTUPDCALLBACK updateCallback;
} vfEntity;

/* MODULE INIT AND TERMINATE FUNCTIONS */
VFAPI void vfInit(void);
VFAPI void vfTerminate(void);

/* THREADING RELATED FUNCTIONS */
VFAPI void vfThreadSleepTime(unsigned int miliseconds);

/* STRUCT CREATION FUNCTIONS */
VFAPI vfVector vfCreateVector(float x, float y);
VFAPI vfColor vfCreateColor(int r, int g, int b, int a);
VFAPI vfTransform* vfCreateTransformv(vfVector vector);
VFAPI vfTransform* vfCreateTransforma(vfVector vector, float rotation,
	float scale);
VFAPI vfTransform* vfCreateTransformp(vfTransform* parent);
VFAPI vfBound* vfCreateBoundt(vfTransform* body);
VFAPI vfBound* vfCreateBounda(vfTransform* body, vfVector position,
	vfVector dimensions);
VFAPI vfParticle* vfCreateParticlet(vfTransform* transform);
VFAPI vfParticle* vfCreateParticlea(vfTransform* transform, vgTexture texture,
	vgShape shape, unsigned char layer);
VFAPI vfPhysics vfCreatePhysics(float bounciness, float drag, float mass);
VFAPI vfPhysics vfCreatePhysicsa(float bounciness, float drag, float mass,
	int moveable, int rotationLock);
VFAPI vfEntity* vfCreateEntity(unsigned char layer, vgShape shape,
	vgTexture texture, vfPhysics physics, vfVector boundPosition, 
	vfVector boundDimensions);

/* STRUCT DESTRUCTION FUNCTIONS */
VFAPI void vfDestroyTransform(vfTransform* transform, int zero);
VFAPI void vfDestroyBound(vfBound* bound, int zero);
VFAPI void vfDestroyParticle(vfParticle* particle, int zero);
VFAPI void vfDestroyEntity(vfEntity* entity, int zero);

/* STRUCT RELATED FUNCTIONS */
VFAPI vfHandle vfGetTransformHandle(vfTransform* transform);
VFAPI vfHandle vfGetBoundHandle(vfBound* bound);
VFAPI vfHandle vfGetParticleHandle(vfParticle* particle);
VFAPI vfHandle vfGetEntityHandle(vfEntity* entity);
VFAPI void* vfGetObject(vfHandle handle, int type);

/* RENDERING FUNCTIONS */
VFAPI void vfRenderParticles(void);
VFAPI void vfRenderEntities(void);
VFAPI void vfRenderBounds(void);

/* PHYSICS RELATED FUNCTIONS */
VFAPI void vfSetPhysicsState(int value);
VFAPI void vfSetCollisionCallback(vfEntity* entity, ENTCOLCALLBACK callback);
VFAPI void vfSetUpdateCallback(vfEntity* entity, ENTUPDCALLBACK callback);

/* DATA RELATED FUNCTIONS */
VFAPI int vfGetBuffer(void* buffer, int size, int type);
VFAPI int vfGetBufferField(void* field, int size, int type);
VFAPI int vfGetObjectCount(int type);
VFAPI void* vfMTAlloc(int size, int zero);
VFAPI int vfMTFree(void* ptr, int size, int zero);

#endif 
