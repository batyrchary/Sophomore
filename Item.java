import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Item
{
    public int itemID;
    public float widthRequest;
    public float heightRequest;
    public boolean isItAssigned=false;


    public Item(int itemID, float widthRequest, float heightRequest)
    {
        this.itemID=itemID;
        this.widthRequest=widthRequest;
        this.heightRequest=heightRequest;
        this.isItAssigned=false;

    }

    public Item(Item t)
    {
        this.itemID=t.itemID;
        this.widthRequest=t.widthRequest;
        this.heightRequest=t.heightRequest;
        this.isItAssigned=t.isItAssigned;
    }

    public  float getWidth()
    {
        return widthRequest;
    }
    public  float getHeight()
    {
        return heightRequest;
    }

    public static boolean ContainsItem(ArrayList<Item> items, Item item)
    {
        boolean contains=false;

        for(int i=0; i<items.size();i++)
        {
            if(items.get(i).itemID==item.itemID)
            {
                contains=true;
                break;
            }
        }
        return contains;
    }

    public static ArrayList<Item> ItemSorter(ArrayList<Item> items, String type, String typeOfOrder)
    {
        ArrayList<Item> ret=new ArrayList<>();

        for(int i=0; i<items.size(); i++)
        {
            Item t=new Item(items.get(i));
            ret.add(t);
        }
        if(type.equals("All"))
        {
            Collections.sort(ret, new Comparator<Item>()
            {
                @Override public int compare(Item p1, Item p2)
                {
                    return (int)((p1.widthRequest*p1.heightRequest) - (p2.widthRequest*p2.heightRequest)); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Item::getWidth)); //smallest to largest
        }


        if(type.equals("Width"))
        {
            Collections.sort(ret, new Comparator<Item>()
            {
                @Override public int compare(Item p1, Item p2)
                {
                    return (int)(p1.widthRequest - p2.widthRequest); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Item::getWidth)); //smallest to largest
        }

        if(type.equals("Height"))
        {
            Collections.sort(ret, new Comparator<Item>()
            {
                @Override public int compare(Item p1, Item p2)
                {
                    return (int)(p1.heightRequest - p2.heightRequest); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Item::getHeight)); //smallest to largest
        }

        if(typeOfOrder.equals("decreasing"))
        {
            Collections.reverse(ret);
        }
        return ret;
    }
}