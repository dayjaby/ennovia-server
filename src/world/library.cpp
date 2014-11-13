#include "world/library.hpp"
#include "world/locatable.hpp"
#include "world/map.hpp"
#include "world/optionlist.hpp"
namespace Ennovia
{


LocatableContainer::LocatableContainer() : last_index(0) {}
int LocatableContainer::create(int id,const std::string& name) {
    container.insert(container_type::value_type(id,new Locatable(Position(),name)));
    return id;
}
int LocatableContainer::create(const std::string& name) {
    int new_id = ++last_index;
    container.insert(container_type::value_type(new_id,new Locatable(Position(),name)));
    return new_id;
}
int LocatableContainer::create(Locatable* loc) {
    int new_id = ++last_index;
    container.insert(container_type::value_type(new_id,loc));
    return new_id;
}
Locatable* LocatableContainer::get(int id) {
    container_type::left_iterator i = container.left.find(id);
    if(i!=container.left.end()) {
        return i->second;
    } else {
        return 0;
    }
}
int LocatableContainer::get(Locatable* loc) {
    container_type::right_iterator i = container.right.find(loc);
    if(i!=container.right.end()) {
        return i->second;
    } else {
        return 0;
    }
}

bool LocatableContainer::exists(int id) {
    return get(id)!=0;
}

ConnectionContainer::ConnectionContainer() {}
int ConnectionContainer::create(int id,boost::shared_ptr<Connection> connection) {
    container.insert(container_type::value_type(id,connection));
    return id;
}

boost::shared_ptr<Connection> ConnectionContainer::get(int id) {
    container_type::left_iterator i = container.left.find(id);
    if(i!=container.left.end()) {
        return i->second;
    } else {
        return boost::shared_ptr<Connection>();
    }
}
int ConnectionContainer::get(boost::shared_ptr<Connection> connection) {
    container_type::right_iterator i = container.right.find(connection);
    if(i!=container.right.end()) {
        return i->second;
    } else {
        return 0;
    }
}

bool ConnectionContainer::exists(int id) {
    return get(id)!=0;
}

MapContainer::MapContainer() {}

int MapContainer::create(int id,Map* map) {
    container.insert(container_type::value_type(id,map));
    return id;
}
Map* MapContainer::get(int id) {
    container_type::left_iterator i = container.left.find(id);
    if(i!=container.left.end()) {
        return i->second;
    } else {
        return 0;
    }
}
int MapContainer::get(Map* map) {
    container_type::right_iterator i = container.right.find(map);
    if(i!=container.right.end()) {
        return i->second;
    } else {
        return 0;
    }
}
bool MapContainer::exists(int id) {
    return get(id)!=0;
}

OptionListContainer::OptionListContainer() : last_index(0) {}

int OptionListContainer::create(OptionList* ol) {
    container.insert(container_type::value_type(++last_index,ol));
    return last_index;
}
OptionList* OptionListContainer::get(int id) {
    container_type::left_iterator i = container.left.find(id);
    if(i!=container.left.end()) {
        return i->second;
    } else {
        return 0;
    }
}
int OptionListContainer::get(OptionList* ol) {
    container_type::right_iterator i = container.right.find(ol);
    if(i!=container.right.end()) {
        return i->second;
    } else {
        return 0;
    }
}
bool OptionListContainer::exists(int id) {
    return get(id)!=0;
}

}

