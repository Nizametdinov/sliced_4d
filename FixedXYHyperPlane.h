#ifndef __FixedXYHyperPlane_h_
#define __FixedXYHyperPlane_h_

#include "HyperPlane.h"

// √иперплоскость с фиксированной плоскостью XY
// Ќормаль такой плоскости имеет вид {cos(alpha), 0, 0, sin(alpha)},
// где alpha - угол поворат вокруг плоскости XY.
// ѕервоначально alpha = 0, а нормаль = {1, 0, 0, 0}
class FixedXYHyperPlane: public HyperPlane
{
public:
	FixedXYHyperPlane(void);
	~FixedXYHyperPlane(void);

	// ѕоворот вокруг плоскости параллельной XY содержащей точку fixedPoint
	// Ќад поведением функции RotateAroundXY еще нужно подумать:
	// нужно ли сохран€ть внутренние координаты fixedPoint после поворота?
	void RotateAroundXY(float angle, const Vector4f &fixedPoint);

	// —двиг гиперплоскости по направлению (shift > 0) или против направлени€ нормали
	void Shift(float shift);

	//  оординаты проекции точки во внутренней системе координат гиперплоскости
	// —истема координат поворачиваетс€ так, что нормаль плоскости становитс€
	// равной {1, 0, 0, 0}, и берутс€ x-, y-, z-координаты точки в повернутой системе 
	virtual Ogre::Vector3 GetInnerCoordinates(const Vector4f &point) const;
	// ќпераци€ обратна€ предыдущей: получение глобальных координат точки, лежащей  
	// на плоскости, по внутренним координатам
	virtual Vector4f GetGlobalCoordinates(const Ogre::Vector3 &innerPoint) const;
private:
};

#endif // __FixedXYHyperPlane_h_