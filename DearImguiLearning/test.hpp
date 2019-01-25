#pragma once


namespace SOUNDS {
	enum ALL {
		MONSTER0, MONSTER1, MONSTER2,
		PLAYER0, PLAYER1, PLAYER2,
		AMBIENT0, AMBIENT1, AMBIENT2,
		COUNT
	};
}

namespace CONTEXTS {
	enum NAMESPACE {
		MONSTER, PLAYER, AMBIENT, COUNT
	};
}


class VirtualClass {
	

public:
	SOUNDS::ALL *whatAmI;
	virtual void playSound(SOUNDS::ALL soundType) = 0;
};


class MonsterSounds : public VirtualClass {
public:
	void playSound(SOUNDS::ALL soundType) {

	}
};

class PlayerSounds : public VirtualClass {
public:
	void playSound(SOUNDS::ALL soundType) {

	}
};

class AmbientSounds : public VirtualClass {
public:
	void initialize() {
		allSounds[CONTEXTS::MONSTER] = new MonsterSounds;
		allSounds[CONTEXTS::PLAYER] = new PlayerSounds;
		allSounds[CONTEXTS::AMBIENT] = new AmbientSounds;
	}
	void playSound(SOUNDS::ALL soundType) {
		this->mySounds[soundType].play();
	}
};



class MainClass {
private:
	VirtualClass* allSounds[CONTEXTS::NAMESPACE::COUNT];

public:
	MainClass() {}
	virtual ~MainClass(){}
	void initialize() {
		allSounds[CONTEXTS::MONSTER] = new MonsterSounds;
		allSounds[CONTEXTS::PLAYER] = new PlayerSounds;
		allSounds[CONTEXTS::AMBIENT] = new AmbientSounds;
	}
	void run(SOUNDS::ALL whatistheEnum, CONTEXTS::NAMESPACE whatistheContext) {
		
		this->allSounds[whatistheContext]->playSound(whatistheEnum);

	}
}