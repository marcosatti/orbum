#pragma once

class PS2Resources_t;

class PS2ResourcesSubobject
{
public:
	explicit PS2ResourcesSubobject(const PS2Resources_t *const PS2Resources);

	virtual ~PS2ResourcesSubobject();

	/*
	Returns the root resources object.
	*/
	inline const PS2Resources_t * getRoot() const;

private:
	const PS2Resources_t *const mPS2Resources;
};

const PS2Resources_t* PS2ResourcesSubobject::getRoot() const
{
	return mPS2Resources;
}
