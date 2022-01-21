#ifndef HANDLE_H
#define HANDLE_H

class Handle {
 public:
  [[nodiscard]] unsigned int getId() const;
  void setId(unsigned int id);

 private:
  unsigned int _id;
};

#endif  // HANDLE_H
