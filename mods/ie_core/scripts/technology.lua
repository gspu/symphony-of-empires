-- Mechanical theory series
mechanical_theory_i = Technology:new{
    ref_name = "mechanical_theory_i",
    name = "Mechanical theory I",
    description = "Relying on natural sources such as the wind, they will be the stepping stone for future developments",
    cost = 10.0,
    type = TECH_ECONOMIC
}
mechanical_theory_i:register()

mechanical_theory_ii = Technology:new{
    ref_name = "mechanical_theory_ii",
    name = "Mechanical theory II",
    description = "The boom in science will help more complex machinery to rise",
    cost = 1800.0,
    type = TECH_ECONOMIC
}
mechanical_theory_ii:register()
mechanical_theory_ii:requires_technology(mechanical_theory_i)

mechanical_theory_iii = Technology:new{
    ref_name = "mechanical_theory_iii",
    name = "Mechanical theory III",
    description = "With the use of power generators it's possible to automate the movement of machines",
    cost = 1800.0,
    type = TECH_ECONOMIC
}
mechanical_theory_iii:register()
mechanical_theory_iii:requires_technology(mechanical_theory_ii)

voltaic_pile = Technology:new{
    ref_name = "voltaic_pile",
    name = _("Voltaic pile"),
    description = "An early battery",
    cost = 15.0,
    type = TECH_ECONOMIC
}
voltaic_pile:register()

combustion_engine = Technology:new{
    ref_name = "combustion_engine",
    name = "Combustion engine",
    description = "",
    cost = 50.0,
    type = TECH_ECONOMIC
}
combustion_engine:register()

steam_locomotive = Technology:new{
    ref_name = "steam_locomotive",
    name = "Steam locomotive",
    description = "",
    cost = 100.0,
    type = TECH_ECONOMIC
}
steam_locomotive:register()

assembly_line = Technology:new{
    ref_name = "assembly_line",
    name = "Assembly line",
    description = "",
    cost = 100.0,
    type = TECH_ECONOMIC
}
assembly_line:register()
assembly_line:requires_technology(mechanical_theory_iii)

napoleonic_tought = Technology:new{
    ref_name = "napoleonic_tought",
    name = "Napoleonic tought",
    description = "",
    cost = 10.0,
    type = TECH_STRATEGIC
}
napoleonic_tought:register()

trench_warfare = Technology:new{
    ref_name = "trench_warfare",
    name = "Trench warfare",
    description = "",
    cost = 1500.0,
    type = TECH_STRATEGIC
}
trench_warfare:register()