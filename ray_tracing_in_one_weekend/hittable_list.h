#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
  std::vector<shared_ptr<Hittable>> m_objects;

  HittableList() {}
  HittableList(shared_ptr<Hittable> object) { add(object); }

  void clear() { m_objects.clear(); }
  void add(shared_ptr<Hittable> object) { m_objects.push_back(object); }

  virtual bool hit(
      const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

#endif