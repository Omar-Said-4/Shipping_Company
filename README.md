# Shipping_Company
### A simulator to a shipping company which needs to handle the cargo delivery in the most efficient and profitable way through automating the cargo assignment up to delivery proceses, to achieve good and fair use of its trucks.
## **Description:**
- It's implemented using cpp, object oriented programming (OOP) and data structures.
- it takes from the user an input file containing all the company data (Events, Trucks ,Cargos) including execution time.
- **It has three modes for outputting the results:**
1. Interactive mode, which allows the user to monitor the cargos and the trucks (waiting for user input), in addition to the output file.
2. step by step mode,  which updates the console automatically without waiting for the user input, in addition to the output file.
3. Silent mode, which produces only an output file with no console output. 
### Classes used:
1. Company (Maestro class).
2. Trucks (Vip, special, Normal).
3. Cargos (Vip, Special, Normal).
4. Events (Base abstract class).
5. PreparationEvent (Preparation of a cargo Inherited from events class).
6. PrompteEvent (Promotion of a Normal cargo to VIP inherited from events class).
7. CancelEvent (cancellation of a Normal cargo inherited from events class).
8. UI (user Interface).
### Data structures used:
- Linked lists.
- Priority queues (for assignment based on priority equations).
- Queues (for the first in first out (FIFO) criteria of cargos and trucks).
## Implementation Details:
- **Loading Rule:** If some cargos are ready and waiting to be assigned to a truck,
don’t start loading cargos as long as the number of ready cargos is less than
capacity of the fist available truck (TC).
- **Maximum Wait Rule:** If there is an available truck that is suitable for a cargo that
has been waiting for MaxW hours (or more), such cargo should be immediately
loaded and moved to its destination. MaxW is loaded from input file. Ignore
“Loading Rule” in this case.
- A truck can’t be loaded with more than one cargo type in the same journey.
- **For normal cargos ONLY**, if a cargo waits more than AutoP days from its
preparation time to be assigned to a truck, it should be automatically
promoted to be an VIP cargo. (AutoP is read from the input file).
### Assignment Order: (if TC cargos of certain type are ready)
1. First, assign VIP cargos (based on a priority equation) to ANY available truck of any type. However, there is a
priority based on the truck type: first choose from VIP trucks THEN normal
trucks THEN special trucks. This means that we do not use normal trucks unless
all VIP trucks are out, and we do not use special trucks unless trucks of all other
types are out.
2. Second, assign special cargos using the available special trucks ONLY. If no
special truck is available, wait until one comes back.
3. Third, assign normal cargos using any type of trucks EXCEPT special trucks.
First use the available normal trucks THEN VIP trucks (if all normal trucks are
out).
4. If a cargo cannot be assigned on the current hour, it should wait for the next
hour. On the next hour, it should be checked whether the cargo can be assigned
now or not. If not, it should wait again and so on.
## Some Definitions
- **Preparation Time (PT):** The time (day:hour) at which the cargo is ready
to be assigned to a truck.
- **Move Time (MT):** The time at which the truck carrying the cargo starts to
move to deliver the cargo.
- **Waiting Cargo:** The cargo that is ready (i.e. cargo’s PT < current time) but
the cargo is not loaded to a truck yet or loaded but the truck doesn’t move yet.
At each hour, you should choose the cargo(s) to assign from the uloaded cargos.
- **Waiting Time (WT):** The time from the preparation of a cargo until its
truck starts to move to deliver it.
WT = MT - PT
- **Moving Cargo:** The cargo that is on its way but is not delivered yet.
- **Delivered Cargo:** The cargo that has been delivered.
- **Cargo Delivery Time (CDT):**
Once a cargo reaches its destination, it should be unloaded from the truck. The
truck then moves on to deliver the remaining cargos or returns back to the
company if this is the last cargo it has.
CDT = MT + Cargo Distance/Truck Speed + Cargo Unload Time
- **Truck Active Time:** Time a truck is loading or in delivering cargos. This
doesn’t include time for a truck to return after delivery.
- **Truck utilization: (percentage):**
tDC/(TC*N) * (tAT/TSim) , N ≠ 0 (if N=0, utilization = 0%)
- **tDC:** total cargos delivered by this truck, TC: truck capacity,
- **N:** total delivery journeys of this truck
- **tAT:** total truck active time
- **TSim:** total Simulation time.
## Teammates
- Amr Salah.
- Ahmed Samy.
