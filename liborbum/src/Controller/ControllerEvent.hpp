#pragma once

/// Describes a controller event (variant).
/// These events are from an external perspective of the controller.
struct ControllerEvent
{
    /// Type of event.
    enum class Type
    {
        Time,
        HBlank,
        VBlank
    } type;

    /// Additional data, context determined from type.
    union {
        double time_us; // Time event: time passed in microseconds.
        int amount;     // HBlank, VBlank: amount of times it occurred.
    } data;
};