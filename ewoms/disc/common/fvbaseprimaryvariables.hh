/*
  Copyright (C) 2011-2014 by Andreas Lauser

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 * \file
 *
 * \copydoc Ewoms::FvBasePrimaryVariables
 */
#ifndef EWOMS_FV_BASE_PRIMARY_VARIABLES_HH
#define EWOMS_FV_BASE_PRIMARY_VARIABLES_HH

#include <dune/common/fvector.hh>

#include "fvbaseproperties.hh"

namespace Ewoms {

/*!
 * \ingroup FvBaseDiscretization
 *
 * \brief Represents the primary variables used by the a model.
 */
template <class TypeTag>
class FvBasePrimaryVariables
    : public Dune::FieldVector<typename GET_PROP_TYPE(TypeTag, Scalar),
                               GET_PROP_VALUE(TypeTag, NumEq)>
{
    typedef typename GET_PROP_TYPE(TypeTag, Scalar) Scalar;
    enum { numEq = GET_PROP_VALUE(TypeTag, NumEq) };
    typedef Dune::FieldVector<Scalar, numEq> ParentType;

public:
    FvBasePrimaryVariables()
        : ParentType()
    { Valgrind::SetUndefined(*this); }

    /*!
     * \brief Construction from a scalar value
     */
    FvBasePrimaryVariables(Scalar value)
        : ParentType(value)
    { }

    /*!
     * \brief Assignment from another primary variables object
     */
    FvBasePrimaryVariables(const FvBasePrimaryVariables &value)
        : ParentType(value)
    { }

    /*!
     * \brief Assign the primary variables "somehow" from a fluid state
     *
     * That is without considering any consistency issues which the
     * fluid state might have. This method is guaranteed to produce
     * consistent results if the fluid state is consistent to the
     * properties at a given spatial location. (Where "consistent
     * results" means that the same fluid state can be reconstructed
     * from the primary variables.)
     */
    template <class FluidState>
    void assignNaive(const FluidState &fluidState)
    {
        OPM_THROW(std::runtime_error,
                  "The PrimaryVariables class does not define a assignNaive() method");
    }
    /*!
     * \brief Instruct valgrind to check the definedness of all
     *        attributes of this class.
     */
    void checkDefined() const
    {
        Valgrind::CheckDefined(*static_cast<const ParentType*>(this));
    }
};

} // namespace Ewoms

#endif