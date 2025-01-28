package lab3;


import java.util.*;

/*
 * Класс, реализующий алгоритм коммивояжера
 */
class Salesman {
    protected final List<PriorityQueue<Edge>> graph = new LinkedList<>(); // введённый граф
    private StringBuilder resultWay; // итоговый путь
    private final LinkedHashSet<Integer> currentWay = new LinkedHashSet<>(); // текущий путь во время работы алгоритма
    private Integer minWayLength; // длина минимального пути
    private int currentWayLength = 0; // текущая длина пути во время работы алгоритма
    private long time; // затраченное время на работу алгоритма
    private final int START_BACKTRACKING_VERTEX = 1; // стартовая вершина. Может быть любой из существующих.
    int graphSize; // размер графа. Хранится для оптимизации времени.

    /*
     * Класс направленного ребра
     * без начальной вершины
     */
    protected class Edge implements Comparable<Edge> {
        int to; // конечная вершина
        int weight; // вес ребра

        /*
         * Конструктор, заполняющий все поля
         */
        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }

        /*
         * Сравнение двух рёбер по весу
         */
        @Override
        public int compareTo(Edge o) {
            return Integer.compare(weight, o.weight);
        }
    }

    /*
     * Чтение графа, выполнение алгоритма и печать результата
     */
    public Salesman() {
        readGraph();
        runSalesman();
        printResult();
    }

    /*
     * Чтение графа в формате
     * <размер>
     * <граф в табличном виде>
     * отсутсвие ребра: "-", отсутствие петли: "inf"
     */
    private void readGraph() {
        Scanner scanner = new Scanner(System.in);
        graphSize = scanner.nextInt();
        for (int i = 1; i <= graphSize; i++) {
            graph.add(new PriorityQueue<>());
            for (int j = 1; j <= graphSize; j++) {
                String buf = scanner.next();
                if (!buf.equals("inf") && !buf.equals("-")) {
                    graph.get(i - 1).add(new Edge(j, Integer.valueOf(buf)));
                }
            }
        }
    }

    /*
     * Запуск алгоритма коммивояжера с вершины START_BACKTRACKING_VERTEX
     * Фиксация затраченного времени
     */
    private void runSalesman() {
        currentWay.add(START_BACKTRACKING_VERTEX);
        long currentTimeMillis = System.currentTimeMillis();
        backtracking(START_BACKTRACKING_VERTEX);
        time = System.currentTimeMillis() - currentTimeMillis;
    }

    /*
     * Печать результата работы алгоритима
     */
    private void printResult() {
        if (minWayLength != null) {
            System.out.println("Way: " + resultWay);
            System.out.println("Distance: " + minWayLength);
            System.out.println("Time: " + time + "mls");
        } else {
            System.out.println("There is no way");
        }
    }

    /*
     * Алгоритм бэктрекинга для поиска минимального пути
     */
    private void backtracking(int vertex) {
        Queue<Edge> queue = new PriorityQueue<>(graph.get(vertex - 1));
        if (currentWay.size() == graphSize || queue.isEmpty()) {
            while (!queue.isEmpty()) {
                Edge edge = queue.poll();
                if (edge.to == START_BACKTRACKING_VERTEX && (minWayLength == null || currentWayLength < minWayLength)) {
                    currentWayLength += edge.weight;
                    minWayLength = currentWayLength;
                    saveWay();
                    currentWayLength -= edge.weight;
                }
            }
            return;
        }
        while (!queue.isEmpty()) {
            Edge edge = queue.poll();
            if ((minWayLength == null || currentWayLength + edge.weight + getSpanningTreeSize((HashSet<Integer>) currentWay.clone(), edge.to) + 1 < minWayLength) && currentWay.add(edge.to)) {
                currentWayLength += edge.weight;
                backtracking(edge.to);
                currentWayLength -= edge.weight;
                currentWay.remove(edge.to);
            }
        }
    }

    /*
     * Поиск минимального остовного дерева для вершин, не входящих в usedVertex, начиная со startVertex
     */
    private double getSpanningTreeSize(HashSet<Integer> usedVertex, int startVertex) {
        PriorityQueue<Edge> queueOfEdge = new PriorityQueue<>();
        int sizeOfTree = 0;
        queueOfEdge.addAll(graph.get(startVertex - 1));
        while (!queueOfEdge.isEmpty() && usedVertex.size() != graphSize) {
            Edge currentEdge = queueOfEdge.poll();
            if (!usedVertex.contains(currentEdge.to)) {
                usedVertex.add(currentEdge.to);
                sizeOfTree += currentEdge.weight;
                queueOfEdge.addAll(graph.get(currentEdge.to - 1));
            }
        }
        return sizeOfTree;
    }

    /*
     * Сохранение текущего пути как оптимального
     */
    private void saveWay() {
        resultWay = new StringBuilder();
        for (int vertex : currentWay) {
            resultWay.append(vertex).append("-");
        }
        resultWay.append(START_BACKTRACKING_VERTEX);
    }
}

public class Main {
    public static void main(String[] args) {
        new Salesman();
    }
}