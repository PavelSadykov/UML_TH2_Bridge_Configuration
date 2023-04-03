//
//  main.cpp
//  UML ДЗ 2 Мост и Компоновщик
//
//  Created by Павел on 02.04.2023.
//
#include <iostream>
#include <vector>

// Transport.h
class Transport {
public:
    virtual void loadGoods() = 0;
};
//класс самосвал для перевозки сыпучих материалов
class DumpTruck : public Transport {
public:
    void loadGoods() override {
        std::cout << "Перевозка и разгрузка сыпучего материала  самосвалом " << std::endl;
    }
};
//класс автомобиль для перевозки мелких грузов
class Car : public Transport {
public:
    void loadGoods() override {
        std::cout << "Перевозка и разгрузка мелкогабаритного груза автомобилем" << std::endl;
    }
};

//класс бензовоз для перевозки топлива
class FuelTanker : public Transport {
public:
    void loadGoods() override {
        std::cout << "Перевозка и разгрузка нефтепродуктов бензовозом" << std::endl;
    }
};


// Storage.h
class Storage {
public:
    Storage(Transport* transport) : transport_(transport) {}
    virtual void receiveGoods() = 0;
    virtual void storeGoods() = 0;
protected:
    Transport* transport_;
};
//класс склад для хранения сыпучих материалов
class Warehouse : public Storage {
public:
    Warehouse(Transport* transport) : Storage(transport) {}
    void receiveGoods() override {
        transport_->loadGoods();
    }
    void storeGoods() override {
        std::cout << "Прием и хранение  сыпучего материала на складе " << std::endl;
    }
};
//класс гараж для хранения мелких грузов
class Garage : public Storage {
public:
    Garage(Transport* transport) : Storage(transport) {}
    void receiveGoods() override {
        transport_->loadGoods();
    }
    void storeGoods() override {
        std::cout << "Прием и хранение груза в гараже" << std::endl;
    }
};
//класс резервуар для хранения топлива
class StorageTank : public Storage {
public:
    StorageTank(Transport* transport) : Storage(transport) {}
    void receiveGoods() override {
        transport_->loadGoods();
    }
    void storeGoods() override {
        std::cout << "Прием и хранение нефтепродуктов на нефтебазе" << std::endl;
    }
};


// StorageComposite.h

class StorageComposite : public Storage {
public:
    StorageComposite(Transport* transport) : Storage(transport) {}
    void add(Storage* storage) {
        storages_.push_back(storage);
    }
    void receiveGoods() override {
        for (Storage* storage : storages_) {
            storage->receiveGoods();
        }
    }
    void storeGoods() override {
        for (Storage* storage : storages_) {
            storage->storeGoods();
        }
    }
private:
    std::vector<Storage*> storages_;
};



int main(int argc, const char * argv[]) {
    int X=0,Y=0;
        Transport* truck = new DumpTruck ();
        Transport* car = new Car();
        Transport* tanker = new FuelTanker ();
        Storage* warehouse = new Warehouse(truck);
        Storage* garage = new Garage(car);
        Storage* storagetank = new StorageTank(tanker);
        StorageComposite* composite = new StorageComposite(truck);
    do{
        std::cout<<"\nВыберете тип груза, для логистической  обработки :"<< std::endl;
        std::cout<<"1 - сыпучий груз"<<std::endl;
        std::cout<<"2 - мелкогабаритный груз"<<std::endl;
        std::cout<<"3 - нефтепродукты"<<std::endl;
        std::cout<<"4 - завершение работы"<<std::endl;
        std::cout<<"-->";
        std::cin>>Y;
        switch (Y) {
            case 1:
                composite->add(warehouse);
                composite->receiveGoods();
                composite->storeGoods();
                break;
            case 2:
                composite->add(garage);
                composite->receiveGoods();
                composite->storeGoods();
                break;
            case 3:
                composite->add(storagetank);
                composite->receiveGoods();
                composite->storeGoods();
                break;
            case 4:
                std::cout<<"Работа завершена"<<std::endl;
                exit(0);
                break;
            default:
                std::cout<<"Введите корректное значение"<<std::endl;
                break;
        }
       
    } while(X!=5);

    return 0;
}
