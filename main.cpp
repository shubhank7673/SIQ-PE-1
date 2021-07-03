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
  private:
    vector<Slot*>slots;
    unordered_map<int,unordered_set<string>>age_to_car_numbers;
    unordered_map<string,int>car_number_to_slot;
    unordered_map<int,unordered_set<int>>age_to_slots;
    priority_queue<int,vector<int>,greater<int>>nearest_free_slot;
  public:
    Parkinglot(int n)
    {
      for(int i = 0;i<n;i++)
      {
        Slot* newSlot = new Slot(1);
        this->slots.push_back(newSlot);
        nearest_free_slot.push(i+1);
      }
      cout<<"Created parking of "<<n<<" slots\n";
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
        cout<<"Parking lot is full\n";
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
      cout<<"Car with vehicle registration number \""+car_number+"\" has been parked at slot number "+to_string(nearest_slot+1)<<"\n";
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
      cout<<"Slot number "+to_string(slot)+" vacated, the car with vehicle registration number \""+car_number+"\" left the space, the driver of the car was of age "+to_string(age)<<"\n";
    }
    void get_car_numbers_by_age(int age)
    {
      if(age_to_car_numbers[age].size() == 0)
      {
        cout<<"\n";
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
        cout<<"\n";
        return;
      }
      cout<<car_number_to_slot[car_number]<<"\n";
    }
    void get_slots_by_age(int age)
    {
      if(age_to_slots[age].size() == 0)
      {
        cout<<"\n";
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
// function to split input string/query by space
vector<string> split(string &s)
{
  vector<string>splitted;
  string temp = "";
  for(auto c:s)
  {
    if(c == ' ')
    {
      splitted.push_back(temp);
      temp = "";
    }
    else
    {
      temp += c;
    }
  }
  splitted.push_back(temp);
  return splitted;
}
// Main driver code
int main() {
  freopen("input.txt","r",stdin);
  string query;
  Parkinglot* parkingservice;
  while(getline(cin,query))
  {
    vector<string> splitted = split(query);
    if(splitted[0] == "Create_parking_lot")
    {
      parkingservice = new Parkinglot(stoi(splitted[1]));
    }
    else if(splitted[0] == "Park")
    {
      parkingservice->parkCar(splitted[1], stoi(splitted[3]));
    }
    else if(splitted[0] == "Leave")
    {
      parkingservice->leave(stoi(splitted[1]));
    }
    else if(splitted[0] == "Slot_number_for_car_with_number")
    {
      parkingservice->get_slot_by_car_number(splitted[1]);
    }
    else if(splitted[0] == "Slot_numbers_for_driver_of_age")
    {
      parkingservice->get_slots_by_age(stoi(splitted[1]));
    }
    else if(splitted[0] == "Vehicle_registration_number_for_driver_of_age")
    {
      parkingservice->get_car_numbers_by_age(stoi(splitted[1]));
    }
  }
}