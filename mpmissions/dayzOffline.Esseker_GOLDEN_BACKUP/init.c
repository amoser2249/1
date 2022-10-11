void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	//weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	//weather.GetRain().Set( 0, 0, 0);
	//weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
	//GetCEApi().ExportProxyData(vector.Zero, 100000);

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 10, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);
	int starthour, startmin, forceyear;

	forceyear = 2021; //To get full moon
	starthour = 22;
	startmin = 0;

	GetGame().GetWorld().SetDate(year, reset_month, reset_day, starthour, startmin);
	
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
        string shepID = "76561199328231261";

        string steamID = player.GetIdentity().GetPlainId();

        player.RemoveAllItems();
		
        if (steamID == shepID)
        {
        	itemEnt = player.GetInventory().CreateInInventory("Shep_M65");
            itemEnt = player.GetInventory().CreateInInventory("Shep_Balaclava");
            itemEnt = player.GetInventory().CreateInInventory("Shep_M2001");
            itemEnt = player.GetInventory().CreateInInventory("Shep_Cargos");
            itemEnt = player.GetInventory().CreateInInventory("Shep_Visor");
            itemEnt = player.GetInventory().CreateInInventory("Fingerless_Gloves");
            itemEnt = player.GetInventory().CreateInInventory("JungleBoots_Black");
        }
        else
        {
        	itemEnt = player.GetInventory().CreateInInventory("Atlas_Halloween_Tshirt_1");
        }
        if (steamID != shepID)
        {
            int throwDice = Math.RandomInt( 1, 5 );
            switch ( throwDice )
            {
				case 1:
                    itemEnt = player.GetInventory().CreateInInventory( "AthleticShoes_Grey" );
					break;
                case 2:
                    itemEnt = player.GetInventory().CreateInInventory( "AthleticShoes_Black" );
					break;
                case 3:
                    itemEnt = player.GetInventory().CreateInInventory( "AthleticShoes_Green" );
					break;
                case 4:
                    itemEnt = player.GetInventory().CreateInInventory( "AthleticShoes_Blue" );
					break;
                case 5:
                    itemEnt = player.GetInventory().CreateInInventory( "AthleticShoes_Beige" );
					break;
            }
			
            int throwAgain = Math.RandomInt( 1, 5 );
            switch ( throwAgain )
            {
				case 1:
                    itemEnt = player.GetInventory().CreateInInventory( "CargoPants_Blue" );
					break;
                case 2:
                    itemEnt = player.GetInventory().CreateInInventory( "CargoPants_Grey" );
					break;
                case 3:
                    itemEnt = player.GetInventory().CreateInInventory( "CargoPants_Black" );
					break;
                case 4:
                    itemEnt = player.GetInventory().CreateInInventory( "CargoPants_Beige" );
					break;
                case 5:
                    itemEnt = player.GetInventory().CreateInInventory( "CargoPants_Green" );
					break;
            }
			

		}
		// top
		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				SetRandomHealth( itemEnt );
				itemBs.SetQuantity( 6 );
				itemBs.SetCleanness( 1 );
			}
            string chemlightArray[] = { "Chemlight_Green", "Chemlight_Yellow", "Chemlight_Blue", "Chemlight_Red" };
			int rndIndex = Math.RandomInt(0, 3);
			itemEnt = itemClothing.GetInventory().CreateInInventory(chemlightArray[rndIndex]);
			SetRandomHealth(itemEnt);

			rand = Math.RandomFloatInclusive(0.0, 1.0);
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory("Apple");
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory("Pear");
			else
				itemEnt = player.GetInventory().CreateInInventory("Plum");

			SetRandomHealth(itemEnt);
			
		}

		// pants
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
 		if ( itemClothing )
        {
        	if (steamID != shepID)
            {
                SetRandomHealth( itemClothing );
               
            }
            else
            {
                itemEnt = itemClothing.GetInventory().CreateInInventory( "PetrolLighter" );
            }

        }
        

		// shoes
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
		if ( itemClothing )
		{
			if (steamID != shepID)
				{
					SetRandomHealth( itemClothing );
				
				}
		}

	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}