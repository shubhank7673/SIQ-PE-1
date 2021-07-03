#include <bits/stdc++.h>
using namespace std;

class Slot{
  public:
    bool isFree;
    int age;
    string car_number;
    Slot(bool status)
    {
      isFree = status;
    }
    void set_data(bool status,string car_number,int age)
    {
      isFree = status;
      this->age = age;
      this->car_number = car_number;
    }
};
class Parkinglot{
  public:
    vector<Slot*>slots;
    unordered_map<int,unordered_set<string>>age_to_car_numbers;
    unordered_map<string,int>car_number_to_slot;
    unordered_map<int,unordered_set<int>>age_to_slots;
    priority_queue<int,vector<int>,greater<int>>nearest_free_slot;
    Parkinglot(int n)
    {
      for(int i = 0;i<n;i++)
      {
        Slot* newSlot = new Slot(1);
        this->slots.push_back(newSlot);
        nearest_free_slot.push(i+1);
      }
    }
    bool isFree()
    {
      if(nearest_free_slot.size() >= 1)
      {
        return 1;
      }
      return 0;
    }
    void parkCar(string car_number,int age)
    {
      if(isFree() == 0)
      {
        cout<<"Parking lot is full";
        return;
      }
      int nearest_slot = nearest_free_slot.top();
      nearest_free_slot.pop();
      // getting index of nearest slot
      nearest_slot--;
      slots[nearest_slot]->set_data(0, car_number, age);
      age_to_car_numbers[age].insert(car_number);
      car_number_to_slot[car_number] = nearest_slot+1;
      age_to_slots[age].insert(nearest_slot+1);
      cout<<"Car with vehicle registration number "+car_number+"has been parked at slot number "+to_string(nearest_slot+1)<<"\n";
    }
    void leave(int slot)
    {
      int slot_index = slot-1;
      string car_number = slots[slot_index]->car_number;
      int age = slots[slot_index]->age;
      // deallocating the slot
      slots[slot_index]->set_data(1, "", -1);
      nearest_free_slot.push(slot);
      age_to_car_numbers[age].erase(car_number);
      car_number_to_slot.erase(car_number);
      age_to_slots[age].erase(slot);
      cout<<"Slot number "+to_string(slot)+" vacated, the car with vehicle registration number "+car_number+" left the space, the driver of the car was of age "+to_string(age)<<"\n";
    }
    void get_car_numbers_by_age(int age)
    {
      if(age_to_car_numbers[age].size() == 0)
      {
        cout<<"No data for given age\n";
        return;
      }
      string all_numbers="";
      for(auto number:age_to_car_numbers[age])
      {
        all_numbers += number+",";
      }
      all_numbers.pop_back();
      cout<<all_numbers<<"\n";
    }
    void get_slot_by_car_number(string car_number)
    {
      if(car_number_to_slot.find(car_number) == car_number_to_slot.end())
      {
        cout<<"No data from given car number\n";
        return;
      }
      cout<<car_number_to_slot[car_number]<<"\n";
    }
    void get_slots_by_age(int age)
    {
      if(age_to_slots[age].size() == 0)
      {
        cout<<"No data for given age\n";
        return;
      }
      string all_slots="";
      for(auto slot:age_to_slots[age])
      {
        all_slots += to_string(slot)+",";
      }
      all_slots.pop_back();
      cout<<all_slots<<"\n";
    }
};
// Main driver code
int main() {
  int n = 6;
  Parkinglot* parkingservice = new Parkinglot(6);
}