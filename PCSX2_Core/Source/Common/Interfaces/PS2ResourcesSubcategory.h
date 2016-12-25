#pragma once

class PS2Resources_t;

class PS2ResourcesSubcategory
{
public:
	explicit PS2ResourcesSubcategory(const PS2Resources_t * PS2Resources);
	virtual ~PS2ResourcesSubcategory();

	/*
	On root resources being created, this function may be called to initalise any resources that depend on others.
	*/
	virtual void postResourcesInit();

	/*
	Returns the root resources object.
	*/
	const PS2Resources_t * getRoot() const;

private:
	/*
	Internal pointer to the root of the resources.
	*/
	const PS2Resources_t * mPS2Resources;
};

