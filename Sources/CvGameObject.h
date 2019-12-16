#pragma once

//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:    CvGameObject.h
//
//  PURPOSE: Wrapper classes for Civ4 game objects, to avoid memory leaks stored in the objects themselves
//
//------------------------------------------------------------------------------------------------
#ifndef CV_GAME_OBJECT_H
#define CV_GAME_OBJECT_H

#include "CvProperties.h"
#include "CvPropertyManipulators.h"
#include "BoolExpr.h"
#include "CvPython.h"

class CvGameObjectGame;
class CvGameObjectTeam;
class CvGameObjectPlayer;
class CvGameObjectCity;
class CvGameObjectUnit;
class CvGameObjectPlot;
class CvGame;
class CvTeam;
class CvPlayer;
class CvCity;
class CvUnit;
class CvPlot;
class CvProperties;

class CvGameObject
{
public:
	virtual GameObjectTypes getGameObjectType() const = 0;
	virtual CvProperties* getProperties() const = 0;
	virtual const CvProperties* getPropertiesConst() const = 0;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func) = 0;
	virtual void foreachOn(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);
	virtual void foreachNear(GameObjectTypes eType, bst::function<void (CvGameObject*)> func, int iDistance);
	virtual void foreachRelated(GameObjectTypes eType, RelationTypes eRelation, bst::function<void (CvGameObject*)> func, int iData = 0);
	virtual void foreachRelatedCond(GameObjectTypes eType, RelationTypes eRelation, bst::function<void (CvGameObject*)> func, BoolExpr* pExpr = NULL, int iData = 0);
	virtual void enumerate(std::vector<CvGameObject*>& kEnum, GameObjectTypes eType);
	virtual void enumerateOn(std::vector<CvGameObject*>& kEnum, GameObjectTypes eType);
	virtual void enumerateNear(std::vector<CvGameObject*>& kEnum, GameObjectTypes eType, int iDistance);
	virtual void enumerateRelated(std::vector<CvGameObject*>& kEnum, GameObjectTypes eType, RelationTypes eRelation, int iData = 0);
	virtual void enumerateRelatedCond(std::vector<CvGameObject*>& kEnum, GameObjectTypes eType, RelationTypes eRelation, BoolExpr* pExpr = NULL, int iData = 0);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func) = 0;

	virtual void eventPropertyChanged(PropertyTypes eProperty, int iNewValue);

	virtual bool isTag(TagTypes eTag) const;
	virtual int getAttribute(AttributeTypes eAttribute) const;
	virtual bool hasGOM(GOMTypes eType, int iID) = 0;

	virtual CvGameObjectPlayer* getOwner() = 0;
	virtual CvGameObjectPlot* getPlot() = 0;
	virtual CvGameObjectTeam* getTeam() = 0;

	virtual void* createPythonWrapper(PyObject*& pyObj) = 0;
	virtual void disposePythonWrapper(void* pArgument) = 0;

	virtual int adaptValueToGame(int iID, int iValue) const;
};

// Python wrapper specialization
namespace Cy
{
	template <>
	struct PyWrap<CvGameObject*> : PyWrapBase
	{
		typedef CvGameObject* value_type;

		PyWrap(const value_type& obj) : obj(obj)
		{
			wrapper = obj->createPythonWrapper(pyobj);
		}

		virtual ~PyWrap()
		{
			obj->disposePythonWrapper(wrapper);
		}

		void* wrapper;
		value_type obj;
	};
}

DECLARE_PY_WRAPPED(CvGameObject*);

class CvGameObjectGame : public CvGameObject
{
public:
	CvGameObjectGame();
	virtual GameObjectTypes getGameObjectType() const;
	virtual CvProperties* getProperties() const;
	virtual const CvProperties* getPropertiesConst() const;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func);

	virtual int getAttribute(AttributeTypes eAttribute) const;
	virtual bool hasGOM(GOMTypes eType, int iID);

	virtual CvGameObjectPlayer* getOwner();
	virtual CvGameObjectPlot* getPlot();
	virtual CvGameObjectTeam* getTeam();

	virtual void* createPythonWrapper(PyObject*& pyObj);
	virtual void disposePythonWrapper(void* pArgument);
};

class CvGameObjectTeam : public CvGameObject
{
public:
	explicit CvGameObjectTeam(CvTeam* pTeam);
	virtual GameObjectTypes getGameObjectType() const;
	virtual CvProperties* getProperties() const;
	virtual const CvProperties* getPropertiesConst() const;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func);

	virtual bool hasGOM(GOMTypes eType, int iID);
	
	virtual CvGameObjectPlayer* getOwner();
	virtual CvGameObjectPlot* getPlot();
	virtual CvGameObjectTeam* getTeam();

	virtual void* createPythonWrapper(PyObject*& pyObj);
	virtual void disposePythonWrapper(void* pArgument);

protected:
	CvTeam* m_pTeam;
};

class CvGameObjectPlayer : public CvGameObject
{
public:
	explicit CvGameObjectPlayer(CvPlayer* pPlayer);
	virtual GameObjectTypes getGameObjectType() const;
	virtual CvProperties* getProperties() const;
	virtual const CvProperties* getPropertiesConst() const;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func);

	virtual bool hasGOM(GOMTypes eType, int iID);
	virtual bool isTag(TagTypes eTag) const;
	
	virtual CvGameObjectPlayer* getOwner();
	virtual CvGameObjectPlot* getPlot();
	virtual CvGameObjectTeam* getTeam();

	virtual void* createPythonWrapper(PyObject*& pyObj);
	virtual void disposePythonWrapper(void* pArgument);

	virtual int adaptValueToGame(int iID, int iValue) const;

protected:
	CvPlayer* m_pPlayer;
};

class CvGameObjectCity : public CvGameObject
{
public:
	explicit CvGameObjectCity(CvCity* pCity);
	virtual GameObjectTypes getGameObjectType() const;
	virtual CvProperties* getProperties() const;
	virtual const CvProperties* getPropertiesConst() const;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);
	virtual void foreachRelated(GameObjectTypes eType, RelationTypes eRelation, bst::function<void (CvGameObject*)> func, int iData = 0);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func);

	virtual void eventPropertyChanged(PropertyTypes eProperty, int iNewValue);

	virtual int getAttribute(AttributeTypes eAttribute) const;
	virtual bool isTag(TagTypes eTag) const;
	virtual bool hasGOM(GOMTypes eType, int iID);
	
	virtual CvGameObjectPlayer* getOwner();
	virtual CvGameObjectPlot* getPlot();
	virtual CvGameObjectTeam* getTeam();

	virtual void* createPythonWrapper(PyObject*& pyObj);
	virtual void disposePythonWrapper(void* pArgument);

	virtual int adaptValueToGame(int iID, int iValue) const;

protected:
	CvCity* m_pCity;
};

class CvGameObjectUnit : public CvGameObject
{
public:
	explicit CvGameObjectUnit(CvUnit* pUnit);
	virtual GameObjectTypes getGameObjectType() const;
	virtual CvProperties* getProperties() const;
	virtual const CvProperties* getPropertiesConst() const;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func);

	virtual void eventPropertyChanged(PropertyTypes eProperty, int iNewValue);

	virtual bool isTag(TagTypes eTag) const;
	virtual bool hasGOM(GOMTypes eType, int iID);
	
	virtual CvGameObjectPlayer* getOwner();
	virtual CvGameObjectPlot* getPlot();
	virtual CvGameObjectTeam* getTeam();

	virtual void* createPythonWrapper(PyObject*& pyObj);
	virtual void disposePythonWrapper(void* pArgument);

	virtual int adaptValueToGame(int iID, int iValue) const;

protected:
	CvUnit* m_pUnit;
};

class CvGameObjectPlot : public CvGameObject
{
public:
	explicit CvGameObjectPlot(CvPlot* pPlot);
	virtual GameObjectTypes getGameObjectType() const;
	virtual CvProperties* getProperties() const;
	virtual const CvProperties* getPropertiesConst() const;
	virtual void foreach(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);
	virtual void foreachOn(GameObjectTypes eType, bst::function<void (CvGameObject*)> func);
	virtual void foreachNear(GameObjectTypes eType, bst::function<void (CvGameObject*)> func, int iDistance);
	virtual void foreachRelated(GameObjectTypes eType, RelationTypes eRelation, bst::function<void (CvGameObject*)> func, int iData = 0);

	virtual void foreachManipulator(bst::function<void (CvGameObject*, CvPropertyManipulators*)> func);

	virtual bool isTag(TagTypes eTag) const;
	virtual bool hasGOM(GOMTypes eType, int iID);
	
	virtual CvGameObjectPlayer* getOwner();
	virtual CvGameObjectPlot* getPlot();
	virtual CvGameObjectTeam* getTeam();

	virtual void* createPythonWrapper(PyObject*& pyObj);
	virtual void disposePythonWrapper(void* pArgument);

protected:
	CvPlot* m_pPlot;
};

#endif
