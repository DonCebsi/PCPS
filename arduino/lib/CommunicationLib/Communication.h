#pragma once

#include <inttypes.h>

#include "Sensors.h"
#include "Plant.h"
#include "Plant.h"

/// The type of a message
enum MessageType {
    PING    = 0,
    STATE   = 1,
    SENSORS = 2,
    SPEC    = 3,
    NEEDMORE = 4,
    MESSAGE_TYPE_MAX = 4,
};

/// One information unit for transport.
class Message {
    private:
        bool allocatedPayload = false;

    public:
        MessageType type;
        uint8_t id;
        uint32_t timestamp;
        void* payload;

        /// Creates a empty Message
        Message();

        /// Deletes a Message
        ~Message();

        /// Construct a message from it's type, a timestamp and a payload.
        /// The payload union must be valid for the message type.
        /// If the type is PING, the payload is discarded.
        Message(MessageType type, uint8_t id, uint32_t timestamp, void* payload);

        /// Construct a message from an encoded String
        Message(const char* bytes);

        /// Build a byte representation of the message. Returns a pointer to the bytes
        /// and takes a reference to an int to store the length in.
        /// It is your responsibility to free the returned pointer with delete[].
        char* encodeBytes(int& len) const;

        /// Returns the length of this message type in bytes.
        static const size_t length(MessageType type);

        /// Move assignment.
        Message& operator=(Message&& other);

    private:
        static const size_t HEADER_LEN = 6;

        /// Deallocates the underlying buffer.
        void deallocate();
};

/// Exposes communication with the rasbpi in a high-level way.
class Communicator {
    private:
        int id;

    public:
    /// Constructs a new Communicator with id
    Communicator(uint8_t id);

    /// Creates a message of the given type and sends it
    void sendPing() const;
    void sendState(const Plant& Plant) const;
    void sendSensorValues(const FullMeasurements& measurements) const;
    void sendSpec(const PlantSpec& spec) const;
    void sendNeedMore() const;

    /// Sends a message over X Bee
    void sendMessage(const Message& message) const;

    /// Tries to receive a message. If one is avaible returns true
    /// and fills the passed message struct. Otherwise returns false
    bool recvMessage(Message& message) const;
};
