#include "Resources/Ee/Vpu/Vu/VuUnitRegisters.hpp"

void VuUnitRegister_Status::set_z_flag_sticky(const uword value)
{
    uword zs = extract_field(ZS);
    insert_field(ZS, zs | value);
    insert_field(Z, value);
}

void VuUnitRegister_Status::set_s_flag_sticky(const uword value)
{
    uword ss = extract_field(SS);
    insert_field(SS, ss | value);
    insert_field(S, value);
}

void VuUnitRegister_Status::set_u_flag_sticky(const uword value)
{
    uword us = extract_field(US);
    insert_field(US, us | value);
    insert_field(U, value);
}

void VuUnitRegister_Status::set_o_flag_sticky(const uword value)
{
    uword os = extract_field(OS);
    insert_field(OS, os | value);
    insert_field(O, value);
}

void VuUnitRegister_Status::set_i_flag_sticky(const uword value)
{
    uword is = extract_field(IS);
    insert_field(IS, is | value);
    insert_field(I, value);
}

void VuUnitRegister_Status::set_d_flag_sticky(const uword value)
{
    uword ds = extract_field(DS);
    insert_field(DS, ds | value);
    insert_field(D, value);
}

void VuUnitRegister_Status::clear_flags()
{
    insert_field(Z, 0);
    insert_field(S, 0);
    insert_field(U, 0);
    insert_field(O, 0);
    insert_field(I, 0);
    insert_field(D, 0);
}

VuUnitRegister_Mac::VuUnitRegister_Mac() :
    status(nullptr)
{
}

void VuUnitRegister_Mac::update_vector_field(const VuVectorField::Field field, const FpuFlags& flags)
{
    // Calculate flag values.
    uword values[4] =
        {
            flags.ZF ? 1U : 0U,
            flags.SF ? 1U : 0U,
            flags.UF ? 1U : 0U,
            flags.OF ? 1U : 0U};

    // Determine if its for x, y, z, w, and update MAC flags.
    const Bitfield* update_flags = nullptr;
    if (field == VuVectorField::Field::X)
        update_flags = X_FLAGS;
    else if (field == VuVectorField::Field::Y)
        update_flags = Y_FLAGS;
    else if (field == VuVectorField::Field::Z)
        update_flags = Z_FLAGS;
    else if (field == VuVectorField::Field::W)
        update_flags = W_FLAGS;
    else
        throw std::runtime_error("Couldn't determine vector field to use - please debug!");

    for (int i = 0; i < 4; i++)
        insert_field(update_flags[i], values[i]);

    // Update the relevant Status flags (Z, S, U, O).
    status->set_z_flag_sticky(values[0]);
    status->set_s_flag_sticky(values[1]);
    status->set_u_flag_sticky(values[2]);
    status->set_o_flag_sticky(values[3]);
}

void VuUnitRegister_Mac::clear_vector_field(const VuVectorField::Field field)
{
    uword values[4] = {0, 0, 0, 0};

    // Determine if its for x, y, z, w, and update MAC flags.
    const Bitfield* update_flags = nullptr;
    if (field == VuVectorField::Field::X)
        update_flags = X_FLAGS;
    else if (field == VuVectorField::Field::Y)
        update_flags = Y_FLAGS;
    else if (field == VuVectorField::Field::Z)
        update_flags = Z_FLAGS;
    else if (field == VuVectorField::Field::W)
        update_flags = W_FLAGS;
    else
        throw std::runtime_error("Couldn't determine vector field to use - please debug!");

    for (int i = 0; i < 4; i++)
        insert_field(update_flags[i], values[i]);

    // Update the relevant Status flags (Z, S, U, O).
    status->set_z_flag_sticky(values[0]);
    status->set_s_flag_sticky(values[1]);
    status->set_u_flag_sticky(values[2]);
    status->set_o_flag_sticky(values[3]);
}

void VuUnitRegister_Clipping::shift_judgement()
{
    write_uword((read_uword() << 6) & 0x00FFFFFF);
}
