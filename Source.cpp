/*
	Finite state machine (FSM) test
	Khalid Ali 2018

	Legal:
		Star Trek and its branding are copyright of CBS Studios Inc.
		References to the branding are included under the legally-acknowledged terms of "fair use"
		
	Notes:
		Based on an assignment from University module for Data Structures & Algorithms for Object-Orientated Programming
		Comes with the DrydockUI class, which is an easy-to-use user interface to operate the program with
		A DrydockUI object is already initialised in main() function and is ready to go
*/

#include "Utility.h" //can be safely removed if DrydockUI is not needed
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma region Enumerations
//Possible states the Drydock can operate in:
	//(Out_Of_Components) Drydock has no components for ship assembly
	//(No_Energy) Drydock has no energy for ship assembly
	//(Has_Energy) Drydock has energy and can assembly a ship
	//(Launching_Ship) Drydock has assembled a ship, which then needs launching
enum state { Out_Of_Components, No_Energy, Has_Energy, Launching_Ship };

//Possible parametres the Drydock can operate with
	//(Components) compoents used for ship assembly
	//(Energy) power used for conducting a ship assembly
enum parametre { Components, Energy };
#pragma endregion 

#pragma region Base classes
class StateContext;

//Base class for other states
//Used in combination with Transition to form a Drydock operating state
class State
{
protected:
	StateContext * currentContext;
public:
	State(StateContext* context) { this->currentContext = context; }
	virtual ~State(void) {}
	virtual void transition(void) {}
};

//Decision contexts
//Facilitates information sharing between state 
class StateContext
{
protected:
	State * currentState = nullptr;
	int stateIndex = 0;
	vector<State*> availableStates;
	vector<unsigned> parametres;
public:
	//State decision context destructor; deletes all available states
	virtual ~StateContext(void)
	{
		//iterate through all available states and release the memory taken by them
		for (unsigned i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i];

		//clear StateContext's vectors
		this->availableStates.clear();
		this->parametres.clear();
	}

	//Allows change of state to be made
	//Parametres:
		//(newState) enumeration of the state to change to
	virtual void setState(state newState)
	{
		//use newState enum as reference of what state to get as currentState
		this->currentState = availableStates[newState];
		this->stateIndex = newState;

		//redundant as individual state transitions are present
		this->currentState->transition();
	}

	//Returns the current operating state
	virtual state getState(void) { return state(stateIndex); }

	//Returns the value used to indicate the current state
	virtual unsigned getStateIndex(void) { return this->stateIndex; }

	//Allows change of parametre value to be made
	//Parametres:
		//(param) enumeration of the parametre to set
		//(value) new value for the enumerated parametre
	void setParamVal(parametre param, unsigned value)
	{
		this->parametres[param] = value;
	}

	//Returns desired parametre value
	//Parametres:
		//(param) enumeration of the parametre to get
	unsigned getParamVal(parametre param) { return this->parametres[param]; }
};

//Base class for events that states have
//Used in combination with State to form a Drydock operating state
class Transition
{
public:
	virtual bool transferEnergy(int energy) { cout << "ERROR: event invalid" << endl; return false; }
	virtual bool makeSelection(int option) { cout << "ERROR: event invalid" << endl; return false; }
	virtual bool supplyComponents(int components) { cout << "ERROR: event invalid" << endl; return false; }
	virtual bool launch(void) { cout << "ERROR: event invalid" << endl; return false; }
};

//Base class for objects being handled by the Drydock
//Inherited by Ship and Weapon subclasses
class Component
{
protected:
	string itemName = "";
	unsigned itemCost = 10000;
	Component(void) {};
public:
	virtual ~Component(void) {}
	virtual string getName(void) { return this->itemName; }
	virtual unsigned getCost(void) { return this->itemCost; }
};

//Base class for a Drydock operating state
//Inherited by specific state classes
class DrydockState : public State, public Transition
{
public:
	DrydockState(StateContext* context) : State(context) {}
};
#pragma endregion

#pragma region Weapon classes
/*
	Object-orientated representation of ship weapons
	The Weapon class is the basis for all ship weapons, which contain two unsigned values for their effectiveness against ship hulls and shields
	Possible Weapon subclasses:
		Type VI Phaser Bank - option code 128
		Type VII Phaser Bank - option code 256
		Type VIII Phaser Array - option code 512
		Type IX Phaser Array - option code 1024
		Type X Phaser Array - option code 2048
		Type XI Phaser Array - option code 4096
		Type XII Phaser Array - option code 8192
*/
class Weapon : public Component
{
protected:
	unsigned powerAgainstHull = 0;
	unsigned powerAgainstShields = 0;
	Weapon(void) {}
private:
	unsigned getPowerAgainstHull(void) { return this->powerAgainstHull; }
	unsigned getPowerAgainstShields(void) { return this->powerAgainstShields; }
};

class PhaserBankVI : public Weapon
{
public:
	PhaserBankVI(void)
	{
		this->itemName = "Type VI Phaser Bank";
		this->itemCost = 500;
		this->powerAgainstHull = 10;
		this->powerAgainstShields = 30;
	}
};

class PhaserBankVII : public Weapon
{
public:
	PhaserBankVII(void)
	{
		this->itemName = "Type VII Phaser Bank";
		this->itemCost = 550;
		this->powerAgainstHull = 20;
		this->powerAgainstShields = 60;
	}
};

class PhaserArrayVIII : public Weapon
{
public:
	PhaserArrayVIII(void)
	{
		this->itemName = "Type VIII Phaser Array";
		this->itemCost = 600;
		this->powerAgainstHull = 40;
		this->powerAgainstShields = 120;
	}
};

class PhaserArrayIX : public Weapon
{
public:
	PhaserArrayIX(void)
	{
		this->itemName = "Type IX Phaser Array";
		this->itemCost = 700;
		this->powerAgainstHull = 80;
		this->powerAgainstShields = 240;
	}
};

class PhaserArrayX : public Weapon
{
public:
	PhaserArrayX(void)
	{
		this->itemName = "Type X Phaser Array";
		this->itemCost = 800;
		this->powerAgainstHull = 160;
		this->powerAgainstShields = 480;
	}
};

class PhaserArrayXI : public Weapon
{
public:
	PhaserArrayXI(void)
	{
		this->itemName = "Type XI Phaser Array";
		this->itemCost = 900;
		this->powerAgainstHull = 320;
		this->powerAgainstShields = 960;
	}
};

class PhaserArrayXII : public Weapon
{
public:
	PhaserArrayXII(void)
	{
		this->itemName = "Type XII Phaser Array";
		this->itemCost = 1000;
		this->powerAgainstHull = 640;
		this->powerAgainstShields = 1920;
	}
};
#pragma endregion

#pragma region Ship classes
/*
	Object-orientated representation of ships
	The Ship class is the basis for all ships, and are composite classes that contain in a weapon inside
	Possible Ship subclasses:
		Saber-class scout - option code 1
		Norway-class science vessel - option code 2
		Steamrunner-class frigate - option code 4
		Akira-class carrier - option code 8
		Prometheus-class cruiser - option code 16
		Sovereign-class heavy cruiser - option code 32
		Excalibur-class battelship - option code 64
*/
class Ship : public Component
{
protected:
	Weapon * mainWeapon = nullptr;
	Ship(void) {};
public:
	virtual ~Ship(void) { delete this->mainWeapon; }
	string getName(void)
	{
		string name = this->itemName;
		if (mainWeapon) name += " + " + this->mainWeapon->getName();
		return name;
	}
	unsigned getCost(void)
	{
		unsigned cost = this->itemCost;
		if (mainWeapon) cost += this->mainWeapon->getCost();
		return cost;
	}
	void addWeapon(Weapon* nWeapon)
	{
		if (!nWeapon)
		{
			cout << "ERROR: cannot accept null Weapon poitner" << endl;
			return;
		}
		this->mainWeapon = nWeapon;
	}
	Weapon* getWeapon(void) { return this->mainWeapon; }
};

class Saber : public Ship
{
public:
	Saber(void)
	{
		this->itemName = "Saber-class scout";
		this->itemCost += 1000;
	}
};

class Norway : public Ship
{
public:
	Norway(void)
	{
		this->itemName = "Norway-class science vessel";
		this->itemCost += 1250;
	}
};

class Steamrunner : public Ship
{
public:
	Steamrunner(void)
	{
		this->itemName = "Steamrunner-class frigate";
		this->itemCost += 1500;
	}
};

class Akira : public Ship
{
public:
	Akira(void)
	{
		this->itemName = "Akira-class carrier";
		this->itemCost += 1750;
	}
};

class Prometheus : public Ship
{
public:
	Prometheus(void)
	{
		this->itemName = "Prometheus-class cruiser";
		this->itemCost += 2000;
	}
};

class Sovereign : public Ship
{
public:
	Sovereign(void)
	{
		this->itemName = "Sovereign-class heavy cruiser";
		this->itemCost += 2500;
	}
};

class Excalibur : public Ship
{
public:
	Excalibur(void)
	{
		this->itemName = "Excalibur-class battleship";
		this->itemCost += 3000;
	}
};
#pragma endregion

#pragma region State classes
//State for when Drydock is out of components
class OutOfComponents : public DrydockState
{
public:
	OutOfComponents(StateContext* context) : DrydockState(context) {}
	bool transferEnergy(int energy);
	bool makeSelection(int option);
	bool supplyComponents(int components);
	bool launch(void);
};

//State for when Drydock is out of energy
class NoEnergy : public DrydockState
{
public:
	NoEnergy(StateContext* context) : DrydockState(context) {}
	bool transferEnergy(int energy);
	bool makeSelection(int option);
	bool supplyComponents(int components);
	bool launch(void);
};

//State for when Drydock has energy
class HasEnergy : public DrydockState
{
public:
	HasEnergy(StateContext* context) : DrydockState(context) {}
	bool transferEnergy(int energy);
	bool makeSelection(int option);
	bool supplyComponents(int components);
	bool launch(void);
};

//State for when Drydock is launching a ship
class LaunchingShip : public DrydockState
{
public:
	LaunchingShip(StateContext* context) : DrydockState(context) {}
	bool transferEnergy(int energy);
	bool makeSelection(int option);
	bool supplyComponents(int components);
	bool launch(void);
};
#pragma endregion

//Actual Drydock state machine driver
class Drydock : public StateContext, public Transition
{
	friend class HasEnergy;
	friend class LaunchingShip;
protected:
	Ship * launchingShip = nullptr;
	bool shipLaunching = false;
	bool shipUnderway = false;
public:
	Drydock(void)
	{
		//initialise Drydock's operating states
		this->availableStates.push_back(new OutOfComponents(this));
		this->availableStates.push_back(new NoEnergy(this));
		this->availableStates.push_back(new HasEnergy(this));
		this->availableStates.push_back(new LaunchingShip(this));

		//initialise Drydock's operating parametres
		this->parametres.push_back(0); //represents Components
		this->parametres.push_back(0); //represents Energy

									   //set starting state
		this->setState(Out_Of_Components);
	}

	~Drydock(void)
	{
		//in the event ship is not underway (triggered by undockShip()), release memory held by the non-underway ship
		if (!this->shipUnderway) delete this->launchingShip;
	}

	//Handles user attempting energy transfer with the current operating state
	//Parametres:
		//(energy) energy to be transferred to power the Drydock
	bool transferEnergy(int energy)
	{
		DrydockState* cState = (DrydockState*)this->currentState;
		return cState->transferEnergy(energy);
	}

	//Handles user attempting ship/component selection with the current operating state
	//Parametres:
		//(option) selection value to indicate the ship configuration desired
	bool makeSelection(int option)
	{
		DrydockState* cState = (DrydockState*)this->currentState;
		return cState->makeSelection(option);
	}

	//Handles user supplying components with the current operating state
	//Parametres:
		//(components) amount of components to supply
	bool supplyComponents(int components)
	{
		DrydockState* cState = (DrydockState*)this->currentState;
		return cState->supplyComponents(components);
	}

	//Handles user attempting launching ship with the current operating state
	bool launch(void)
	{
		DrydockState* cState = (DrydockState*)this->currentState;
		return cState->launch();
	}

	//Releases the assembled ship from Drydock
	Ship* undockShip(void)
	{
		if (this->shipLaunching)
		{
			this->shipLaunching = false;
			this->shipUnderway = true;
			return this->launchingShip;
		}
		else
		{
			cout << "ERROR: no ship assembled" << endl;
			return nullptr;
		}
		return nullptr; //fallback
	}
};

#pragma region OutOfComponents state methods
//Handles user attempting energy transfer when Drydock is out of components
//Parametres:
	//(energy) energy to be transferred to power the Drydock
bool OutOfComponents::transferEnergy(int energy)
{
	//Drydock should block this action since it needs components before it can accept currency

	cout << "ERROR: cannot accept energy due to the absence of components" << endl;
	this->currentContext->setState(Out_Of_Components);
	return false;
}

//Handles user attempting ship/component selection when Drydock is out of components
//Parametres:
	//(option) selection value to indicate the ship configuration desired
bool OutOfComponents::makeSelection(int option)
{
	//Drydock should block this action since it needs components before allowing a selection

	cout << "ERROR: cannot select component due to the absence of components" << endl;
	this->currentContext->setState(Out_Of_Components);
	return false;
}

//Handles user supplying components when Drydock is out of components
//Parametres:
	//(components) amount of components to supply
bool OutOfComponents::supplyComponents(int components)
{
	//Drydock should allow this action since it's required to shift the state

	cout << "Components added: " << components << endl;
	this->currentContext->setParamVal(Components, components);
	this->currentContext->setState(No_Energy);
	return true;
}

//Handles user attempting launching ship when Drydock is out of components
bool OutOfComponents::launch(void)
{
	//Drydock should block this action since it needs components before assembling and then launching a ship

	cout << "ERROR: cannot launch an unassembled ship" << endl;
	this->currentContext->setState(Out_Of_Components);
	return false;
}
#pragma endregion

#pragma region NoEnergy state methods
//Handles user attempting energy transfer when Drydock has no energy
//Parametres:
	//(energy) energy to be transferred to power the Drydock
bool NoEnergy::transferEnergy(int energy)
{
	//Drydock should allow this action since it's required to shift the state

	if (energy <= 0)
	{
		cout << "ERROR: invalid amount of energy supplied";
		this->currentContext->setState(No_Energy);
		return false;
	}

	cout << "Energy transferred: " << energy;
	this->currentContext->setParamVal(Energy, this->currentContext->getParamVal(Energy) + energy);
	cout << ", total: " << this->currentContext->getParamVal(Energy) << endl;
	this->currentContext->setState(Has_Energy);
	return true;
}

//Handles user attempting ship/component selection when Drydock has no energy
//Parametres:
	//(option) selection value to indicate the ship configuration desired
bool NoEnergy::makeSelection(int option)
{
	//Drydock should block this action since it needs energy before allowing a selection

	cout << "ERROR: cannot select component due to the absence of energy" << endl;
	this->currentContext->setState(No_Energy);
	return false;
}

//Handles user supplying components when Drydock has no energy
//Parametres:
	//(components) amount of components to supply
bool NoEnergy::supplyComponents(int components)
{
	//Drydock should block this action since it needs energy before allowing more components to be supplied

	cout << "ERROR: cannot accept component supply due to the absence of energy" << endl;
	this->currentContext->setState(No_Energy);
	return false;
}

//Handles user attempting launching ship when Drydock has no energy
bool NoEnergy::launch(void)
{
	//Drydock should block this action since it needs energy before assembling and then launching a ship

	cout << "ERROR: cannot launch an unassembled ship" << endl;
	this->currentContext->setState(No_Energy);
	return false;
}
#pragma endregion

#pragma region HasEnergy state methods
//Handles user attempting energy transfer when Drydock has energy
//Parametres:
	//(energy) energy to be transferred to power the Drydock
bool HasEnergy::transferEnergy(int energy)
{
	//Drydock should allow this action since it may be required to allow higher component selection

	if (energy <= 0)
	{
		cout << "ERROR: invalid amount of energy supplied";
		this->currentContext->setState(Has_Energy);
		return false;
	}

	cout << "Energy transferred: " << energy;
	this->currentContext->setParamVal(Energy, this->currentContext->getParamVal(Energy) + energy);
	cout << ", total: " << this->currentContext->getParamVal(Energy) << endl;
	this->currentContext->setState(Has_Energy);
	return true;
}

//Handles user attempting ship/component selection when Drydock has energy
//Parametres:
	//(option) selection value to indicate the ship configuration desired
bool HasEnergy::makeSelection(int option)
{
	//Drydock should allow this action since it's required to shift the state

	//Option code for Ship (defaulted as supplied option code in case of no weapon option code give)
	int shipOption = option;
	//Option code for Weapon
	int weaponOption = 0;
	//Temporary Weapon result
	Weapon* weapon = nullptr;
	//Components needed for selection
	unsigned componentsNeeded = 0;

	//(1) attempt to separate the ship and weapon options code, and if needed select the weapon specified
	if (option > 128) //only proceed option is more than 128, meaning only proceed if a potential weapon code is present
	{
		shipOption = (option) % 128; //use division remainder to extract values under 64 (ie. Ship code) 
		weaponOption = option - shipOption;

		switch (weaponOption)
		{
		case 128:

			weapon = new PhaserBankVI;
			componentsNeeded++;
			break;
		case 256:
			weapon = new PhaserBankVII;
			componentsNeeded++;
			break;
		case 512:
			weapon = new PhaserArrayVIII;
			componentsNeeded++;
			break;
		case 1024:
			weapon = new PhaserArrayIX;
			componentsNeeded++;
			break;
		case 2048:
			weapon = new PhaserArrayX;
			componentsNeeded++;
			break;
		case 4096:
			weapon = new PhaserArrayXI;
			componentsNeeded++;
			break;
		case 8192:
			weapon = new PhaserArrayXII;
			componentsNeeded++;
			break;
		default: //fallback
			cout << "ERROR: weapon selection invalid" << endl;
			this->currentContext->setState(Has_Energy);
			return false;
			break;
		}
	}

	//(2) create a Ship object using the Ship option code
	switch (shipOption)
	{
	case 1:
		((Drydock*)(this->currentContext))->launchingShip = new Saber;
		componentsNeeded++;
		break;
	case 2:
		((Drydock*)(this->currentContext))->launchingShip = new Norway;
		componentsNeeded++;
		break;
	case 4:
		((Drydock*)(this->currentContext))->launchingShip = new Steamrunner;
		componentsNeeded++;
		break;
	case 8:
		((Drydock*)(this->currentContext))->launchingShip = new Akira;
		componentsNeeded++;
		break;
	case 16:
		((Drydock*)(this->currentContext))->launchingShip = new Prometheus;
		componentsNeeded++;
		break;
	case 32:
		((Drydock*)(this->currentContext))->launchingShip = new Sovereign;
		componentsNeeded++;
		break;
	case 64:
		((Drydock*)(this->currentContext))->launchingShip = new Excalibur;
		componentsNeeded++;
		break;
	default: //fallback
		cout << "ERROR: ship selection invalid" << endl;
		this->currentContext->setState(Has_Energy);
		return false;
		break;
	}

	//(3) if applicable, pass selected weapon into the assembling ship
	if (weapon) ((Drydock*)(this->currentContext))->launchingShip->addWeapon(weapon);
	cout << "Selected: " << ((Drydock*)(this->currentContext))->launchingShip->getName() << endl;

	//(4) check if there is enough energy for ship assembly
	if (((Drydock*)(this->currentContext))->launchingShip->getCost() > this->currentContext->getParamVal(Energy))
	{
		cout << "ERROR: not enough energy available to construct " << ((Drydock*)(this->currentContext))->launchingShip->getName() << endl;
		if (((Drydock*)(this->currentContext))->launchingShip->getWeapon()) delete ((Drydock*)(this->currentContext))->launchingShip->getWeapon();
		delete ((Drydock*)(this->currentContext))->launchingShip;
		this->currentContext->setState(Has_Energy);
		return false;
	}

	//(5) check if there is enough components for ship assembly
	if (componentsNeeded > this->currentContext->getParamVal(Components))
	{
		cout << "ERROR: not enough components available to construct " << ((Drydock*)(this->currentContext))->launchingShip->getName() << endl;
		if (((Drydock*)(this->currentContext))->launchingShip->getWeapon()) delete ((Drydock*)(this->currentContext))->launchingShip->getWeapon();
		delete ((Drydock*)(this->currentContext))->launchingShip;
		this->currentContext->setState(Has_Energy);
		return false;
	}

	cout << "Constructing: " << ((Drydock*)(this->currentContext))->launchingShip->getName() << endl;
	this->currentContext->setState(Launching_Ship);
	return true;
}

//Handles user supplying components when Drydock has energy
//Parametres:
	//(components) amount of components to supply
bool HasEnergy::supplyComponents(int components)
{
	//Drydock should allow this action since it may be required to allow better component selection

	cout << "Components added: " << components << endl;
	this->currentContext->setParamVal(Components, components);
	this->currentContext->setState(Has_Energy);
	return true;
}

//Handles user attempting launching ship when Drydock has energy
bool HasEnergy::launch(void)
{
	//Drydock should block this action since it needs selection before assembling and then launching a ship

	cout << "ERROR: cannot launch an unassembled ship" << endl;
	this->currentContext->setState(No_Energy);
	return false;
}
#pragma endregion

#pragma region LaunchingShip state methods
//Handles user attempting energy transfer when Drydock is launching a ship
//Parametres:
	//(energy) energy to be transferred to power the Drydock
bool LaunchingShip::transferEnergy(int energy)
{
	//Drydock should block this action since it is busy

	cout << "ERROR: cannot accept energy since Drydock is currently busy" << endl;
	this->currentContext->setState(Launching_Ship);
	return false;
}

//Handles user attempting ship/component selection when Drydock is launching a ship
//Parametres:
	//(option) selection value to indicate the ship configuration desired
bool LaunchingShip::makeSelection(int option)
{
	//Drydock should block this action since it is busy

	cout << "ERROR: cannot select component since Drydock is currently busy" << endl;
	this->currentContext->setState(Launching_Ship);
	return false;
}

//Handles user supplying components when Drydock is launching a ship
//Parametres:
	//(components) amount of components to supply
bool LaunchingShip::supplyComponents(int components)
{
	//Drydock should block this action since it is busy

	cout << "ERROR: cannot accept component supply since Drydock is currently busy" << endl;
	this->currentContext->setState(Launching_Ship);
	return false;
}

//Handles user attempting launching ship when Drydock is launching a ship
bool LaunchingShip::launch(void)
{
	//Drydock should allow this action since it's required to shift the state

	//flag that the ship is launching
	((Drydock*)(this->currentContext))->shipLaunching = true;
	cout << "Launching: " << ((Drydock*)(this->currentContext))->launchingShip->getName() << endl;

	//update component parametre to reflect the successful construction
	int componentsNeeded = 1;
	if (((Drydock*)(this->currentContext))->launchingShip->getWeapon()) componentsNeeded++;
	this->currentContext->setParamVal(Energy, this->currentContext->getParamVal(Components) - componentsNeeded);

	//update energy parametre to reflect the successful construction
	this->currentContext->setParamVal(Energy, this->currentContext->getParamVal(Energy) - ((Drydock*)(this->currentContext))->launchingShip->getCost());

	//check the resultant state of the Drydock
	if (this->currentContext->getParamVal(Components) <= 0)
	{
		//check if Drydock is out of components
		cout << "ALERT: Drydock has ran out of components - using " << this->currentContext->getParamVal(Energy) << " energy to shut down operations" << endl;
		this->currentContext->setParamVal(Energy, 0);
		this->currentContext->setParamVal(Components, 0); //ensure number of components is not less than 0
		this->currentContext->setState(Out_Of_Components);
	}
	else if (this->currentContext->getParamVal(Components) > 0 && this->currentContext->getParamVal(Energy) <= 0)
	{
		//else check if Drydock has no energy left
		this->currentContext->setParamVal(Energy, 0); //ensure energy is not less than 0
		this->currentContext->setState(No_Energy);
	}
	else if (this->currentContext->getParamVal(Components) > 0 && this->currentContext->getParamVal(Energy) > 0)
	{
		//else ensure if Drydock has both surplus components and energy remainingsd
		this->currentContext->setState(Has_Energy);
	}

	//print remaining resources
	cout << "Components remaining: " << this->currentContext->getParamVal(Components) << endl;
	cout << "Energy remaining: " << this->currentContext->getParamVal(Energy) << endl;
	return true;
}
#pragma endregion

//Drydock user interface for diagnosing the state machine
//Can be safely discarded from the code
class DrydockUI
{
private:
	Drydock* drydock = nullptr;
	Ship* ship = nullptr;
	int input = 0;
public:
	DrydockUI(void)
	{
		this->drydock = new Drydock;
		Utility::setColour(WHITE, BLACK);
	}
	~DrydockUI(void) { delete this->drydock; }
	void menu(void)
	{
		cout << "*** DRYDOCK USER INTERFACE ***" << endl;
		cout << "Standard options:" << endl;
		cout << "1) Supply components" << endl;
		cout << "2) Transfer energy" << endl;
		cout << "3) Make selection" << endl;
		cout << "4) Launch ship" << endl;
		cout << "Debug options:" << endl;
		cout << "5) UNDOCK SHIP" << endl;
		cout << "6) DISPLAY PARAMETRES" << endl;
		cout << "7) DISPLAY CURRENT STATE" << endl;
		cout << "8) OVERRIDE STATE" << endl;
		cout << "9) RESET DRYDOCK" << endl;
		int selection = Utility::getInteger("Selection: ", 1, 9);
		switch (selection)
		{
		case 1:
			Utility::clearScreen();
			input = Utility::getInteger("Components to supply: ", -2147483647, 2147483647);
			this->drydock->supplyComponents(input);
			cout << endl << endl;
			this->menu();
			break;
		case 2:
			Utility::clearScreen();
			input = Utility::getInteger("Energy to transfer: ", -2147483647, 2147483647);
			this->drydock->transferEnergy(input);
			cout << endl << endl;
			this->menu();
			break;
		case 3:
			Utility::clearScreen();
			cout << "*** OPTION SELECTION ***" << endl;
			cout << "Ship code:" << endl;
			cout << "1 - Saber-class scout" << endl;
			cout << "2 - Norway-class frigate" << endl;
			cout << "4 - Steamrunner-class frigate" << endl;
			cout << "8 - Akira-class carrier" << endl;
			cout << "16 - Prometheus-class cruiser" << endl;
			cout << "32 - Sovereign-class heavy cruiser" << endl;
			cout << "64 - Excalibur-class battleship" << endl;
			cout << " + Phaser code:" << endl;
			cout << "128 - Type VI Phaser Bank" << endl;
			cout << "256 - Type VII Phaser Bank" << endl;
			cout << "512 - Type VIII Phaser Array" << endl;
			cout << "1024 - Type IX Phaser Array" << endl;
			cout << "2048 - Type X Phaser Array" << endl;
			cout << "4096 - Type XI Phaser Array" << endl;
			cout << "8192 - Type XII Phaser Array" << endl;
			input = Utility::getInteger("Selection: ", -2147483647, 2147483647);
			this->drydock->makeSelection(input);
			cout << endl << endl;
			this->menu();
			break;
		case 4:
			Utility::clearScreen();
			this->drydock->launch();
			cout << endl << endl;
			this->menu();
			break;
		case 5:
			Utility::clearScreen();
			ship = this->drydock->undockShip();
			cout << "Undocked: " << ship->getName();
			delete ship;
			cout << endl << endl;
			this->menu();
			break;
		case 6:
			Utility::clearScreen();
			cout << "Components: " << drydock->getParamVal(Components) << endl;
			cout << "Energy: " << drydock->getParamVal(Energy);
			cout << endl << endl;
			this->menu();
			break;
		case 7:
			Utility::clearScreen();
			switch (this->drydock->getState())
			{
			case Out_Of_Components:
				cout << "Drydock is out of components";
				break;
			case No_Energy:
				cout << "Drydock has no energy";
				break;
			case Has_Energy:
				cout << "Drydock has energy";
				break;
			case Launching_Ship:
				cout << "Drydock is launching a ship";
				break;
			}
			cout << endl << endl;
			this->menu();
			break;
		case 8:
			Utility::clearScreen();
			if (Utility::getYesNo("THIS ACTION CAN BREAK THE STATE MACHINE - CONTINUE (Y/N)? "))
			{
				cout << "*** STATE SELECTION ***" << endl;
				cout << "1) Out of components:" << endl;
				cout << "2) No Energy" << endl;
				cout << "3) Has Energy" << endl;
				cout << "4) Launching Ship" << endl;
				input = Utility::getInteger("Selection: ", 1, 4);
				this->drydock->setState(state(input));
			}
			cout << endl << endl;
			this->menu();
			break;
		case 9:
			if (Utility::getYesNo("THIS ACTION WILL ERASE THE STATE MACHINE - CONTINUE (Y/N)? "))
			{
				delete this->drydock;
				this->drydock = new Drydock;
			}
			Utility::clearScreen();
			cout << endl << endl;
			this->menu();
			break;
		}
	}
};

int main(void)
{
	DrydockUI dUI;
	dUI.menu();
	return 0;
}