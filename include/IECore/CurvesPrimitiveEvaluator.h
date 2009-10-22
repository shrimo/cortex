//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of Image Engine Design nor the names of any
//       other contributors to this software may be used to endorse or
//       promote products derived from this software without specific prior
//       written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#ifndef IECORE_CURVESPRIMITIVEEVALUATOR_H
#define IECORE_CURVESPRIMITIVEEVALUATOR_H

#include "IECore/PrimitiveEvaluator.h"

namespace IECore
{

IE_CORE_FORWARDDECLARE( CurvesPrimitive )

class CurvesPrimitiveEvaluator : public PrimitiveEvaluator
{

	public :

		typedef CurvesPrimitive PrimitiveType;

		IE_CORE_DECLARERUNTIMETYPED( CurvesPrimitiveEvaluator, PrimitiveEvaluator );

		class Result : public PrimitiveEvaluator::Result
		{
			public :

				IE_CORE_DECLAREMEMBERPTR( Result );

				virtual Imath::V3f point() const;
				/// Not yet implemented.
				virtual Imath::V3f normal() const;
				/// U parameter will always be 0.
				virtual Imath::V2f uv() const;
				/// Not yet implemented.
				virtual Imath::V3f uTangent() const;
				virtual Imath::V3f vTangent() const;
				unsigned curveIndex() const;

				virtual Imath::V3f vectorPrimVar( const PrimitiveVariable &pv ) const;
				virtual float floatPrimVar( const PrimitiveVariable &pv ) const;
				virtual int intPrimVar( const PrimitiveVariable &pv ) const;
				virtual const std::string &stringPrimVar( const PrimitiveVariable &pv ) const;
				virtual Imath::Color3f colorPrimVar( const PrimitiveVariable &pv ) const;
				virtual half halfPrimVar( const PrimitiveVariable &pv ) const;
				
			private :
			
				friend class CurvesPrimitiveEvaluator;
			
				Result();
				
				void init( unsigned curveIndex, float v, const CurvesPrimitiveEvaluator *evaluator );
								
				template<typename T>
				T primVar( const PrimitiveVariable &pv, const float *coefficients ) const;
				
				unsigned m_curveIndex;
				float m_v;
				float m_segmentV;
				float m_coefficients[4];
				float m_derivativeCoefficients[4];
				unsigned m_vertexDataIndices[4];
				unsigned m_varyingDataIndices[2];
				PrimitiveVariable m_p;
				
		};
		IE_CORE_DECLAREPTR( Result );

		CurvesPrimitiveEvaluator( ConstCurvesPrimitivePtr curves );
		virtual ~CurvesPrimitiveEvaluator();

		virtual ConstPrimitivePtr primitive() const;
		
		virtual PrimitiveEvaluator::ResultPtr createResult() const;
		virtual void validateResult( const PrimitiveEvaluator::ResultPtr &result ) const;

		//! @name Standard Query Functions
		////////////////////////////////////////////////////////////////////////////////////////
		//@{
		/// Not yet implemented.
		virtual float surfaceArea() const;
		/// Not yet implemented.
		virtual float volume() const;
		/// Not yet implemented.
		virtual Imath::V3f centerOfGravity() const;
		/// Not yet implemented.
		virtual bool closestPoint( const Imath::V3f &p, const PrimitiveEvaluator::ResultPtr &result ) const;
		/// Returns pointAtV( 0, uv[1], result ).
		virtual bool pointAtUV( const Imath::V2f &uv, const PrimitiveEvaluator::ResultPtr &result ) const;
		/// Not yet implemented.	
		virtual bool intersectionPoint( const Imath::V3f &origin, const Imath::V3f &direction,
			const PrimitiveEvaluator::ResultPtr &result, float maxDistance = Imath::limits<float>::max() ) const;
		/// Not yet implemented.	
		virtual int intersectionPoints( const Imath::V3f &origin, const Imath::V3f &direction,
			std::vector<PrimitiveEvaluator::ResultPtr> &results, float maxDistance = Imath::limits<float>::max() ) const;
		//@}

		//! @name Curve specific query functions
		////////////////////////////////////////////////////////////////////////////////////////
		//@{
		bool pointAtV( unsigned curveIndex, float v, const PrimitiveEvaluator::ResultPtr &result ) const;
		//@}

	private :

		friend class Result;

		CurvesPrimitivePtr m_curvesPrimitive;
		const std::vector<int> &m_verticesPerCurve;
		std::vector<int> m_vertexDataOffsets; // one value per curve
		std::vector<int> m_varyingDataOffsets; // one value per curve
		PrimitiveVariable m_p;
		
};

IE_CORE_DECLAREPTR( CurvesPrimitiveEvaluator );

} // namespace IECore

#endif // IECORE_CURVESPRIMITIVEEVALUATOR_H