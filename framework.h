/******************************************************************************
* <framework.h>
* Bailey Jia-Tao Brown
* 2021
* 
*	Header file for abstract graphics and utilites library
*	Contents:
*		- Header guard
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
* 
******************************************************************************/

#ifndef __VFRAMEWORK_INCLUDE__
#define __VFRAMEWORK_INCLUDE__

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

#define VF_BUFFER_SIZE_INIT 0x60
#define VF_BUFFER_SIZE_INCREMENT 0x30
#define VF_PARENT_SEARCH_THRESHOLD 0x20

/* STRUCTURE DEFINITIONS */
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

typedef struct vfBound
{
	int active;
	vfTransform* body;
	vfVector position;
	vfVector dimensions;
} vfBound;

typedef struct vfParticle
{
	int active;
	vgShape shape;
	vgTexture texture;
	vfColor bias;

	vfTransform* transform;
} vfParticle;

typedef unsigned int vfHandle;

/* MODULE INIT AND TERMINATE FUNCTIONS */
VFAPI void vfInit(void);
VFAPI void vfTerminate(void);

/* THREADING RELATED FUNCTIONS */
VFAPI void vfThreadSleepTime(unsigned int miliseconds);

/* STRUCT CREATION FUNCTIONS */
VFAPI vfVector vfCreateVector(float x, float y);
VFAPI vfTransform* vfCreateTransformv(vfVector vector);
VFAPI vfTransform* vfCreateTransforma(vfVector vector, float rotation,
	float scale);
VFAPI vfTransform* vfCreateTransformp(vfTransform* parent);
VFAPI vfBound* vfCreateBoundt(vfTransform* body);
VFAPI vfBound* vfCreateBounda(vfTransform* body, vfVector position,
	vfVector dimensions);
VFAPI vfParticle* vfCreateParticlet(vfTransform* transform);
VFAPI vfParticle* vfCreateParticlea(vfTransform* transform, vgTexture texture,
	vgShape* shape);

/* STRUCT DESTRUCTION FUNCTIONS */
VFAPI void vfDestroyTransform(vfTransform* transform);
VFAPI void vfDestroyBound(vfBound* bound);
VFAPI void vfDestroyParticle(vfParticle* particle);

/* STRUCT RELATED FUNCTIONS */
VFAPI vfHandle vfGetTransformHandle(vfTransform* transform);
VFAPI vfHandle vfGetBoundHandle(vfBound* bound);
VFAPI vfHandle vfGetParticleHandle(vfParticle* particle);
VFAPI vfTransform* vfGetTransform(vfHandle hndl);
VFAPI vfBound* vfGetBound(vfHandle hndl);
VFAPI vfParticle* vfGetParticle(vfHandle hndl);

/* RENDERING FUNCTIONS */
VFAPI void vfRenderParticles(void);

#endif 
