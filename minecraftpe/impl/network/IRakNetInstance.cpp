#include <network/IRakNetInstance.hpp>
#include <network/Packet.hpp>

void IRakNetInstance::send(Packet* a2) {
	delete a2;
}
void IRakNetInstance::send(const RakNet::RakNetGUID&, Packet* a3) {
	delete a3;
}
