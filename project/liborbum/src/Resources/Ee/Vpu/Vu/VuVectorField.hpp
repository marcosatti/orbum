#pragma once

/// Maps vector fields to the internal values the VU uses.
class VuVectorField
{
public:
	enum Field
	{
		X = 0,
		Y = 1,
		Z = 2,
		W = 3,
	};

	static constexpr Field VECTOR_FIELDS[] =
	{
		VuVectorField::X,
		VuVectorField::Y,
		VuVectorField::Z,
		VuVectorField::W
	};
};