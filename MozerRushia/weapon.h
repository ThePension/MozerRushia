#ifndef WEAPON_H
#define WEAPON_H


class Weapon
{
public:
    Weapon();
    void shoot();

private:
    double cadence;
    int damage;
    int speed;
    //enum weaponType;
};

#endif // WEAPON_H
