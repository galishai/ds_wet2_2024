import math

class Player:
    def __init__(self, strength):
        self.strength = strength


class Team:
    def __init__(self, id):
        self.id = id
        self.players = []
        self.player_timer = 0
        self.wins = 0

    def add_player(self, player_strength):
        self.players.append([player_strength, self.player_timer])
        self.player_timer += 1

    def get_newest(self):
        if len(self.players) == 0:
            return 0
        
        lowest_counter = 0
        newest_player = self.players[0]
        
        for p in self.players:
            if p[1] > lowest_counter:
                lowest_counter = p[1]
                newest_player = p

        return newest_player
    
    def remove(self, player):
        self.players.remove(player)

    def get_size(self):
        return len(self.players)
    
    def median(self, lst):
        sorted_lst = sorted(lst)
        n = len(lst)
        return sorted_lst[n//2]
    
    def get_strength(self):
        if self.get_size() == 0:
            return 0
        strength_arr = [p[0] for p in self.players]
        median_strength = self.median(strength_arr)
        return median_strength*self.get_size()
    
    def add_win(self):
        self.wins += 1

    def get_wins(self):
        return self.wins

class Olympics:
    def __init__(self):
        self.teams = []

    def find_team(self, team_id):
        for t in self.teams:
            if t.id == team_id:
                return t
            
        else:
            return False

    def add_team(self, team_id):
        if team_id <= 0:
            return "INVALID_INPUT"
        
        find_result = self.find_team(team_id)
        if find_result == False:
            self.teams.append(Team(team_id))
            return "SUCCESS"
        
        else:
            return "FAILURE"
        
    def remove_team(self, team_id):
        if team_id <= 0:
            return "INVALID_INPUT"
        
        find_result = self.find_team(team_id)
        if find_result == False:
            return "FAILURE"
        
        else:
            self.teams.remove(find_result)
            return "SUCCESS"

    def add_player(self, team_id, player_strength):
        if team_id <= 0 or player_strength <= 0:
            return "INVALID_INPUT"
        
        find_result = self.find_team(team_id)
        if find_result == False:
            return "FAILURE"

        else:
            find_result.add_player(player_strength)
            return "SUCCESS"
        
    def remove_newest_player(self, team_id):
        if team_id <= 0:
            return "INVALID_INPUT"
        
        t = self.find_team(team_id)
        if t == False:
            return "FAILURE"
        
        else:
            newest_player = t.get_newest()
            if newest_player == 0:
                return "FAILURE"
            t.remove(newest_player)
            return "SUCCESS"
        
    def play_match(self, team_id1, team_id2):
        if team_id1 == team_id2 or team_id1 <= 0 or team_id2 <= 0:
            return "INVALID_INPUT"
        
        team1 = self.find_team(team_id1)
        team2 = self.find_team(team_id2)

        if team1 == False or team2 == False:
            return "FAILURE"
        
        if team1.get_size() == 0 or team2.get_size() == 0:
            return "FAILURE"
        
        team1_str = team1.get_strength()
        team2_str = team2.get_strength()
        winner_id = 0

        if team1_str > team2_str:
            team1.add_win()
            winner_id = team_id1

        elif team2_str > team1_str:
            team2.add_win()
            winner_id = team_id2

        else:
            if team1.id < team2.id:
                team1.add_win()
                winner_id = team_id1

            else:
                team2.add_win()
                winner_id = team_id2
        
        return ["SUCCESS", winner_id]
    
    def num_wins_for_team(self, team_id):
        if team_id <= 0:
            return "INVALID_INPUT"
        
        find_result = self.find_team(team_id)
        if find_result == False:
            return "FAILURE"
        
        else:
            return ["SUCCESS", find_result.get_wins()]
        
    def get_highest_ranked_team(self):
        if len(self.teams) == 0:
            return ["SUCCESS", -1]
        
        highest_rank = 0

        for t in self.teams:
            if t.get_size() == 0:
                continue
            
            else:
                rank = t.get_strength() + t.get_wins()
                if rank > highest_rank:
                    highest_rank = rank

        return ["SUCCESS", highest_rank]
    
    def unite_teams(self, team_id1, team_id2):
        if team_id1 == team_id2 or team_id1 <= 0 or team_id2 <= 0:
            return "INVALID_INPUT"
        
        team1 = self.find_team(team_id1)
        team2 = self.find_team(team_id2)

        if team1 == False or team2 == False:
            return "FAILURE"
        
        team2_players_by_time = sorted(team2.players, key=lambda x: x[1])
        for p in team2_players_by_time:
            team1.add_player(p[0])
            team2.remove(p)

        self.remove_team(team_id2)
        return "SUCCESS"
    
    def is_power_of_two(self, n):
        return (n & (n-1) == 0) and n != 0
    
    def play_tournament(self, low_power, high_power):
        if low_power <=0 or high_power<=0 or high_power < low_power or low_power == high_power:
            return "INVALID_INPUT"
        
        teams_range = [t for t in self.teams if t.get_strength() >= low_power and t.get_strength() <= high_power]
        # print([f"{t.id}-{t.get_strength()}" for t in teams_range])
        teams_range = sorted([t for t in self.teams if low_power <= t.get_strength() <= high_power], key=lambda t: t.get_strength())
        # print([f"{t.id}-{t.get_strength()}" for t in teams_range])

        if not self.is_power_of_two(len(teams_range)):
            return "FAILURE"

        num_teams = len(teams_range)
        num_rounds = int(math.log(num_teams, 2))

        index = int(num_teams/2)
        for i in range(0, num_rounds):
            for j in range(index, num_teams):
                teams_range[j].add_win()
            
            index = index + int((num_teams-index)/2)

        return ["SUCCESS", teams_range[-1].id]
    

'''
# teams_range = [0,0,0,0,0,0,0,0]
    # num_teams = 8
    # num_rounds = int(math.log(num_teams, 2))

    # index = int(num_teams/2)
    # for i in range(0, num_rounds):
    #     for j in range(index, num_teams):
    #         teams_range[j]+=1
        
    #     index = index + int((num_teams-index)/2)
'''