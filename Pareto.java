import java.util.ArrayList;

public class Pareto {

    public static Population crowding_distance_assignment(Population I)
    {
        int l=I.size();
        for(int i=0; i<l; i++)
        {
            I.get(i).distance=0;
        }
        Population p=new Population();

        Population pb=p.sortByFitness(I, "bin");
        pb.get(0).distance=10000;
        pb.get(l-1).distance=10000;

        for(int i=1; i<l-2; i++)
        {
            pb.get(i).distance=pb.get(i).distance+(pb.get(i+1).getFitness("bin")-pb.get(i-1).getFitness("bin"))/(1-0);
        }
        Population pl=p.sortByFitness(pb, "latency");
        pl.get(0).distance=10000;
        pl.get(l-1).distance=10000;

        for(int i=1; i<l-2; i++)
        {
            pl.get(i).distance=pl.get(i).distance+((pl.get(i+1).getFitness("latency")-pl.get(i-1).getFitness("latency"))/(1-0));
        }
        return pl;
    }

    public static Population ParetoSelection(Population parentOffspring)
    {
        ArrayList<Population> Fis = Fast_non_dominanted_sort(parentOffspring);

        Population retf=new Population();

        int counter=0;
        Population cdaAll=new Population();
        for(int i=0; i<Fis.size(); i++)
        {
        //    System.out.println("fisSize="+Fis.size());
            counter=counter+Fis.get(i).size();
        //    System.out.println("counter="+counter);
            Population cda=crowding_distance_assignment(Fis.get(i));
         //   System.out.println("Fis="+Fis.get(i).size());
         //   System.out.println("Cda="+cda.size());

            for(int j=0; j<cda.size();j++)
            {
                cdaAll.add(cda.get(j));
            }
            if(counter>=parentOffspring.size()/2)
                break;
        }


     //   System.out.println(cdaAll.size()/2);

        for(int j=0; j<parentOffspring.size()/2; j++)
        {
            retf.add(new Chromosome(cdaAll.get(j)));
        }
        return retf;
    }


    public static ArrayList<Population> Fast_non_dominanted_sort(Population P)
    {
 //       System.out.println("population in FNDS="+P.size());

        Population NotUsed=new Population();

        for(int i=0; i<P.size(); i++)
        {
            NotUsed.add(P.get(i));
        }


        ArrayList<Population> Fis=new ArrayList<>();
        Population F1=new Population();
        for(int i=0; i<P.size(); i++) {
            Chromosome p=P.get(i);
            p.np=0;
            p.Sp.clear();
            p.rank=-1;

            for(int j=0; j<P.size(); j++) {
                Chromosome q=P.get(j);
                if(p.getFitness("bin")>=q.getFitness("bin") && p.getFitness("latency")>=q.getFitness("latency")) {
                    p.Sp.add(q);
                }
                else if(p.getFitness("bin")<q.getFitness("bin") && p.getFitness("latency")<q.getFitness("latency")) {

                    p.np=p.np+1;
                }
            }

            if(p.np==0) {
                p.rank=1;

                int index=NotUsed.indexOf(p);
                NotUsed.remove(index);

                F1.add(p);
            }
        }
        Fis.add(F1);

        for(int i=0; i<Fis.size(); i++)
        {
            Population Q=new Population();
            Population Fi=Fis.get(i);

            for(int j=0; j<Fi.size(); j++)
            {
                Chromosome p=Fi.get(j);
                for(int k=0; k<p.Sp.size(); k++)
                {
                    Chromosome q=p.Sp.get(k);
                    q.np=q.np-1;
                    if(q.np==0)
                    {
                        q.rank=(i+1)+1;

                        int index=NotUsed.indexOf(q);
                        NotUsed.remove(index);

                        Q.add(new Chromosome(q));
                    }
                }
            }
          //  System.out.println("Q"+i+"="+Q.size());
            if(Q.size()>0)
                Fis.add(Q);
            //System.out.println("\tQ="+Q.size());
        }
      /*
       System.out.println("FNDSstart");
        for(int i=0; i<Fis.size(); i++)
        {
            System.out.println(Fis.get(i).size());
        }

        System.out.println("FNDSend");

        System.out.println("NotUsed="+NotUsed.size());
        */

      Fis.add(NotUsed);

        return Fis;
        //System.out.println(Fis.size());
    }
}
