///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for tree builders.
 *	\file		OPC_TreeBuilders.cpp
 *	\author		Pierre Terdiman
 *	\date		March, 20, 2001
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	A builder for AABB-trees of AABBs.
 *
 *	\class		AABBTreeOfAABBsBuilder
 *	\author		Pierre Terdiman
 *	\version	1.2
 *	\date		March, 20, 2001
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	A builder for AABB-trees of triangles.
 *
 *	\class		AABBTreeOfTrianglesBuilder
 *	\author		Pierre Terdiman
 *	\version	1.2
 *	\date		March, 20, 2001
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Precompiled Header
#include "stdafx.h"
#pragma hdrstop

namespace Opcode
{
#include "OPC_TreeBuilders.h"
} // namespace Opcode

using namespace Opcode;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Computes the AABB of a set of primitives.
 *	\param		primitives		[in] list of indices of primitives
 *	\param		nb_prims		[in] number of indices
 *	\param		global_box		[out] global AABB enclosing the set of input primitives
 *	\return		true if success
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AABBTreeOfAABBsBuilder::ComputeGlobalBox(const udword* primitives, udword nb_prims, AABB& global_box) const
{
    // Checkings
    if (!primitives || !nb_prims) return false;

    // Initialize global box
    global_box = mAABBList[primitives[0]];

    // Loop through boxes
    for (udword i = 1; i < nb_prims; i++)
    {
        // Update global box
        global_box.Add(mAABBList[primitives[i]]);
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Computes the splitting value along a given axis for a given primitive.
 *	\param		index		[in] index of the primitive to split
 *	\param		axis		[in] axis index (0,1,2)
 *	\return		splitting value
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float AABBTreeOfAABBsBuilder::GetSplittingValue(udword index, udword axis) const
{
    // For an AABB, the splitting value is the middle of the given axis,
    // i.e. the corresponding component of the center point
    return mAABBList[index].GetCenter(axis);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Computes the AABB of a set of primitives.
 *	\param		primitives		[in] list of indices of primitives
 *	\param		nb_prims		[in] number of indices
 *	\param		global_box		[out] global AABB enclosing the set of input primitives
 *	\return		true if success
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AABBTreeOfTrianglesBuilder::ComputeGlobalBox(const udword* primitives, udword nb_prims, AABB& global_box) const
{
    // Checkings
    if (!primitives || !nb_prims) return false;

    // Initialize global box
    Point Min(flt_max, flt_max, flt_max);
    Point Max(flt_min, flt_min, flt_min);

    // Loop through triangles
    for (udword i = 0; i < nb_prims; i++)
    {
        // Get current triangle-vertices
        const Point& p0 = mVerts[mTriList[primitives[i]].mVRef[0]];
        const Point& p1 = mVerts[mTriList[primitives[i]].mVRef[1]];
        const Point& p2 = mVerts[mTriList[primitives[i]].mVRef[2]];
        // Update global box
        Min.Min(p0).Min(p1).Min(p2);
        Max.Max(p0).Max(p1).Max(p2);
    }
    global_box.SetMinMax(Min, Max);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Computes the splitting value along a given axis for a given primitive.
 *	\param		index		[in] index of the primitive to split
 *	\param		axis		[in] axis index (0,1,2)
 *	\return		splitting value
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float AABBTreeOfTrianglesBuilder::GetSplittingValue(udword index, udword axis) const
{
    /*	// Compute center of triangle
        Point Center;
        mTriList[index].Center(mVerts, Center);
        // Return value
        return Center[axis];*/

    // Compute correct component from center of triangle
    return (((const float*)mVerts[mTriList[index].mVRef[0]])[axis] +
               ((const float*)mVerts[mTriList[index].mVRef[1]])[axis] +
               ((const float*)mVerts[mTriList[index].mVRef[2]])[axis]) *
           INV3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Computes the splitting value along a given axis for a given node.
 *	\param		primitives		[in] list of indices of primitives
 *	\param		nb_prims		[in] number of indices
 *	\param		global_box		[in] global AABB enclosing the set of input primitives
 *	\param		axis			[in] axis index (0,1,2)
 *	\return		splitting value
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float AABBTreeOfTrianglesBuilder::GetSplittingValue(
    const udword* primitives, udword nb_prims, const AABB& global_box, udword axis) const
{
    if (mRules & SPLIT_GEOMCENTER) {
        // Loop through triangles
        float SplitValue = 0.0f;
        for (udword i = 0; i < nb_prims; i++)
        {
            // Get current triangle-vertices
            const Point& p0 = mVerts[mTriList[primitives[i]].mVRef[0]];
            const Point& p1 = mVerts[mTriList[primitives[i]].mVRef[1]];
            const Point& p2 = mVerts[mTriList[primitives[i]].mVRef[2]];
            // Update split value
            SplitValue += ((const float*)p0)[axis];
            SplitValue += ((const float*)p1)[axis];
            SplitValue += ((const float*)p2)[axis];
        }
        return SplitValue / float(nb_prims * 3);
    }
    else
        return AABBTreeBuilder::GetSplittingValueEx(primitives, nb_prims, global_box, axis);
}
